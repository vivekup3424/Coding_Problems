import express, { type Request, type Response, type NextFunction } from 'express';
import axios from 'axios';
import jwt from 'jsonwebtoken';
import session from 'express-session';
import dotenv from 'dotenv';
import { readFileSync } from 'fs';
import { type DecodedToken } from './types';

// Load environment variables
dotenv.config();

const app = express();
const PORT = process.env.PORT || 8080;

// Zitadel configuration
const ZITADEL_DOMAIN = process.env.ZITADEL_DOMAIN || 'https://auth.keus.in';
const PROJECT_ID = process.env.PROJECT_ID || '325033691317272582';

// Validate required environment variables
if (!ZITADEL_DOMAIN || !PROJECT_ID) {
    console.error('Missing required environment variables: ZITADEL_DOMAIN, PROJECT_ID');
    process.exit(1);
}

// Service User Credentials Interface
interface ServiceUserCredentials {
    keyId: string;
    key: string;
    clientId: string;
    userId?: string; // Optional for service accounts
}

// Introspection service user credentials (using API grants key)
let introspectionCredentials: ServiceUserCredentials | null = null;

// General service user credentials (using service account key)
let serviceUserCredentials: ServiceUserCredentials | null = null;

try {
    // Load introspection credentials from api.json (for token introspection)
    const apiKeyData = JSON.parse(readFileSync('./keys/api.json', 'utf8'));

    // Validate API credentials structure according to Zitadel documentation
    if (!apiKeyData.keyId || !apiKeyData.key || !apiKeyData.clientId) {
        throw new Error('Invalid API credentials format. Required: keyId, key, clientId');
    }

    introspectionCredentials = {
        keyId: apiKeyData.keyId,
        key: apiKeyData.key,
        clientId: apiKeyData.clientId
    };

    console.log('✅ Introspection credentials loaded successfully');
    console.log(`📋 Introspection Client ID: ${introspectionCredentials.clientId}`);
    console.log(`🔑 Introspection Key ID: ${introspectionCredentials.keyId}`);
} catch (error) {
    console.error('❌ Failed to load introspection credentials:', error);
    console.error('Make sure ./keys/api.json exists and contains valid API credentials');
    process.exit(1);
}

try {
    // Load service user credentials from su.json (for ZITADEL API access)
    const suKeyData = JSON.parse(readFileSync('./keys/su.json', 'utf8'));

    // Validate service user credentials structure according to Zitadel documentation
    if (!suKeyData.keyId || !suKeyData.key) {
        throw new Error('Invalid service user credentials format. Required: keyId, key');
    }

    serviceUserCredentials = {
        keyId: suKeyData.keyId,
        key: suKeyData.key,
        clientId: suKeyData.userId, // For service accounts, userId acts as clientId
        userId: suKeyData.userId
    };

    console.log('✅ Service user credentials loaded successfully');
    console.log(`📋 Service User ID: ${serviceUserCredentials.userId}`);
    console.log(`🔑 Service User Key ID: ${serviceUserCredentials.keyId}`);
} catch (error) {
    console.error('❌ Failed to load service user credentials:', error);
    console.error('Make sure ./keys/su.json exists and contains valid service user credentials');
    process.exit(1);
}

// Middleware
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Enable CORS for frontend
app.use((req, res, next) => {
    const allowedOrigins = process.env.NODE_ENV === 'production'
        ? ['http://heimdall.keus.in']
        : ['http://localhost:3000', 'http://localhost:3001', 'http://localhost:5173'];

    const origin = req.headers.origin;
    if (origin && allowedOrigins.includes(origin)) {
        res.header('Access-Control-Allow-Origin', origin);
    }

    res.header('Access-Control-Allow-Credentials', 'true');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept, Authorization');
    res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');

    if (req.method === 'OPTIONS') {
        res.sendStatus(200);
    } else {
        next();
    }
});

// Session configuration for cookie-based auth
app.use(session({
    secret: process.env.SESSION_SECRET || 'your-session-secret-key-change-this-in-production',
    resave: false,
    saveUninitialized: false,
    cookie: {
        secure: process.env.NODE_ENV === 'production', // Set to true in production with HTTPS
        httpOnly: true,
        maxAge: 24 * 60 * 60 * 1000 // 24 hours
    }
}));

// Extend session interface
declare module 'express-session' {
    interface SessionData {
        state?: string;
        nonce?: string;
        tokens?: {
            access_token: string;
            id_token: string;
            refresh_token?: string;
            token_type?: string;
            expires_in?: number;
        };
        userInfo?: any;
    }
}


// Token introspection using JWT client assertion (recommended by Zitadel)
async function introspectToken(token: string): Promise<{ active: boolean;[key: string]: any }> {
    try {
        if (!introspectionCredentials) {
            throw new Error('Introspection credentials not loaded');
        }

        // Generate JWT client assertion for authentication
        const now = Math.floor(Date.now() / 1000);
        const clientAssertionJWT = jwt.sign({
            iss: introspectionCredentials.clientId,
            sub: introspectionCredentials.clientId,
            aud: ZITADEL_DOMAIN, // Your ZITADEL domain/issuer URL
            exp: now + 3600, // Expires in 1 hour
            iat: now // Issued at time (MUST NOT be older than 1h)
        }, introspectionCredentials.key, {
            algorithm: 'RS256',
            keyid: introspectionCredentials.keyId
        });

        const response = await axios.post(`${ZITADEL_DOMAIN}/oauth/v2/introspect`,
            new URLSearchParams({
                token: token, // The token to introspect
                client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer',
                client_assertion: clientAssertionJWT // Our JWT client assertion
            }), {
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded'
            }
        });

        console.log('Token introspection result:', response.data);
        return response.data;
    } catch (error) {
        console.error('Token introspection failed:', error);
        if (axios.isAxiosError(error)) {
            console.error('Introspection error response:', error.response?.data);
            console.error('Introspection error status:', error.response?.status);
        }
        return { active: false };
    }
}

// JWT validation middleware
async function validateToken(req: Request, res: Response, next: NextFunction): Promise<void> {
    try {
        let token: string | undefined;

        // Check for token in session (cookie-based)
        if (req.session?.tokens?.access_token) {
            token = req.session.tokens.access_token;
        }
        // Check for token in Authorization header
        else if (req.headers.authorization) {
            const authHeader = req.headers.authorization;
            if (authHeader.startsWith('Bearer ')) {
                token = authHeader.substring(7);
            }
        }

        if (!token) {
            res.status(401).json({
                error: 'No token provided',
                message: 'Access token is required. Please login first.'
            });
            return;
        }

        // Introspect token with Zitadel using JWT client assertion
        const introspectionResult = await introspectToken(token);

        if (!introspectionResult.active) {
            res.status(401).json({
                error: 'Invalid token',
                message: 'The provided token is not valid or has expired.'
            });
            return;
        }

        // Validate token expiration from introspection result
        const now = Math.floor(Date.now() / 1000);
        if (introspectionResult.exp && introspectionResult.exp < now) {
            res.status(401).json({
                error: 'Token expired',
                message: 'The token has expired. Please login again.'
            });
            return;
        }

        // Validate token is active and not before its valid time
        if (introspectionResult.nbf && introspectionResult.nbf > now) {
            res.status(401).json({
                error: 'Token not yet valid',
                message: 'The token is not yet valid.'
            });
            return;
        }

        // Decode JWT to get user info for additional information
        const decodedToken = jwt.decode(token) as DecodedToken;

        if (!decodedToken) {
            res.status(401).json({
                error: 'Invalid token format',
                message: 'Unable to decode the token.'
            });
            return;
        }

        // Create user object from introspection result (more reliable than JWT decode)
        const userInfo = {
            sub: introspectionResult.sub || decodedToken.sub,
            email: introspectionResult.email || decodedToken.email,
            email_verified: introspectionResult.email_verified || decodedToken.email_verified,
            name: introspectionResult.name || decodedToken.name,
            given_name: introspectionResult.given_name || decodedToken.given_name,
            family_name: introspectionResult.family_name || decodedToken.family_name,
            preferred_username: introspectionResult.preferred_username || decodedToken.preferred_username,
            picture: introspectionResult.picture || decodedToken.picture,
            iss: introspectionResult.iss || decodedToken.iss,
            aud: introspectionResult.aud || decodedToken.aud,
            exp: introspectionResult.exp || decodedToken.exp,
            iat: introspectionResult.iat || decodedToken.iat,
            client_id: introspectionResult.client_id || decodedToken.client_id,
            // Include project roles for authorization
            project_roles: introspectionResult['urn:zitadel:iam:org:project:roles'] || (decodedToken as any)['urn:zitadel:iam:org:project:roles'],
            specific_project_roles: introspectionResult[`urn:zitadel:iam:org:project:${PROJECT_ID}:roles`] || (decodedToken as any)[`urn:zitadel:iam:org:project:${PROJECT_ID}:roles`]
        };

        // Attach user info to request
        req.user = userInfo;
        next();
    } catch (error) {
        console.error('Token validation error:', error);
        res.status(401).json({
            error: 'Authentication failed',
            message: 'Unable to validate token.'
        });
    }
}



// Extend Request interface to include user
declare global {
    namespace Express {
        interface Request {
            user?: DecodedToken;
        }
    }
}

// Routes

// Health check endpoint
app.get('/health', (req: Request, res: Response) => {
    res.json({
        status: 'healthy',
        timestamp: new Date().toISOString(),
        service: 'zitadel-poc-server'
    });
});

// Store tokens in session (called from frontend after successful login)
app.post('/zitadel-poc/auth/store-tokens', (req: Request, res: Response): void => {
    try {
        const { tokens, userInfo } = req.body;

        if (!tokens || !tokens.access_token) {
            res.status(400).json({
                error: 'Invalid request',
                message: 'Tokens are required'
            });
            return;
        }

        // Store tokens in session
        req.session.tokens = tokens;
        req.session.userInfo = userInfo;

        res.json({
            message: 'Tokens stored successfully',
            success: true
        });
    } catch (error) {
        console.error('Error storing tokens:', error);
        res.status(500).json({
            error: 'Internal server error',
            message: 'Failed to store tokens'
        });
    }
});

// Protected API endpoints

// Get user dashboard data
app.get('/zitadel-poc/user/dashboard', validateToken, (req: Request, res: Response): void => {
    try {
        const user = req.user!;

        // Mock dashboard data
        const dashboardData = {
            welcome_message: `Welcome back, ${user.name || user.preferred_username || 'User'}!`,
            user_stats: {
                login_count: Math.floor(Math.random() * 100) + 1,
                last_login: new Date().toISOString(),
                account_created: new Date(Date.now() - Math.random() * 365 * 24 * 60 * 60 * 1000).toISOString()
            },
            recent_activities: [
                { action: 'Profile Updated', timestamp: new Date().toISOString() },
                { action: 'Password Changed', timestamp: new Date(Date.now() - 24 * 60 * 60 * 1000).toISOString() },
                { action: 'Email Verified', timestamp: new Date(Date.now() - 7 * 24 * 60 * 60 * 1000).toISOString() }
            ],
            permissions: ['read:profile', 'write:profile', 'read:dashboard']
        };

        res.json({
            dashboard: dashboardData,
            message: 'Dashboard data retrieved successfully'
        });
    } catch (error) {
        console.error('Error getting dashboard data:', error);
        res.status(500).json({
            error: 'Internal server error',
            message: 'Failed to get dashboard data'
        });
    }
});

// Logout endpoint
app.post('/zitadel-poc/auth/logout', (req: Request, res: Response) => {
    try {
        // Clear session
        req.session.destroy((err) => {
            if (err) {
                console.error('Error destroying session:', err);
                return res.status(500).json({
                    error: 'Internal server error',
                    message: 'Failed to logout'
                });
            }

            res.json({
                message: 'Logged out successfully',
                success: true
            });
        });
    } catch (error) {
        console.error('Error during logout:', error);
        res.status(500).json({
            error: 'Internal server error',
            message: 'Failed to logout'
        });
    }
});

// Test endpoint for API connectivity
app.get('/zitadel-poc/test', validateToken, (req: Request, res: Response): void => {
    res.json({
        message: 'Protected API is working!',
        user: req.user?.preferred_username || req.user?.name || 'Unknown',
        timestamp: new Date().toISOString(),
        server: 'zitadel-poc-server'
    });
});

// Service User Token Generation Endpoints

// Generate JWT assertion for service user (for ZITADEL API access)
function generateServiceUserJWTAssertion(siteId?: string): string {
    if (!serviceUserCredentials) {
        throw new Error('Service user credentials not loaded');
    }

    const now = Math.floor(Date.now() / 1000);

    const payload: Record<string, any> = {
        iss: serviceUserCredentials.clientId,
        sub: serviceUserCredentials.clientId,
        aud: ZITADEL_DOMAIN,
        exp: now + 300, // Expires in 5 minutes
        iat: now,
    };

    // Add custom claims if siteId is provided
    if (siteId) {
        payload.site_id = siteId;
    }

    return jwt.sign(payload, serviceUserCredentials.key, {
        algorithm: 'RS256',
        keyid: serviceUserCredentials.keyId
    });
}

// Exchange JWT assertion for access token (for ZITADEL API access)
async function getServiceUserAccessToken(jwtAssertion: string, siteId?: string): Promise<any> {
    try {
        const tokenEndpoint = `${ZITADEL_DOMAIN}/oauth/v2/token`;

        // Prepare scopes - include ZITADEL API audience scope as per documentation
        let scopes = 'openid profile';
        // Add ZITADEL API audience scope for access to ZITADEL APIs
        scopes += ' urn:zitadel:iam:org:project:id:zitadel:aud';

        if (PROJECT_ID) {
            scopes += ` urn:zitadel:iam:org:project:id:${PROJECT_ID}:aud`;
        }

        const requestData = {
            grant_type: 'urn:ietf:params:oauth:grant-type:jwt-bearer',
            assertion: jwtAssertion,
            scope: scopes
        };

        const response = await axios.post(tokenEndpoint, requestData, {
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded'
            }
        });

        return {
            access_token: response.data.access_token,
            token_type: response.data.token_type,
            expires_in: response.data.expires_in,
            scope: response.data.scope,
            site_id: siteId || undefined,
            generated_at: new Date().toISOString()
        };
    } catch (error) {
        if (axios.isAxiosError(error) && error.response) {
            throw new Error(`Token exchange failed: ${error.response.status} - ${JSON.stringify(error.response.data)}`);
        } else {
            throw new Error(`Token exchange failed: ${(error as Error).message}`);
        }
    }
}

// Token generation endpoint
app.post('/api/generate-token', async (req: Request, res: Response): Promise<void> => {
    try {
        const { site_id } = req.body;

        // Validate site_id
        if (!site_id || typeof site_id !== 'string' || site_id.trim() === '') {
            res.status(400).json({
                error: 'Invalid request',
                message: 'site_id is required and must be a non-empty string'
            });
            return;
        }

        const trimmedSiteId = site_id.trim();

        console.log(`Generating token for site_id: ${trimmedSiteId}`);

        // Generate JWT assertion with site_id
        const jwtAssertion = generateServiceUserJWTAssertion(trimmedSiteId);

        // Exchange JWT for access token
        const tokenResponse = await getServiceUserAccessToken(jwtAssertion, trimmedSiteId);

        console.log(`Token generated successfully for site_id: ${trimmedSiteId}`);

        res.json({
            success: true,
            message: 'Token generated successfully',
            data: tokenResponse
        });

    } catch (error) {
        console.error('Token generation error:', (error as Error).message);
        res.status(500).json({
            error: 'Token generation failed',
            message: (error as Error).message
        });
    }
});

// Token validation endpoint (using introspection)
app.post('/api/validate-token', async (req: Request, res: Response): Promise<void> => {
    try {
        const { token } = req.body;

        if (!token) {
            res.status(400).json({
                error: 'Invalid request',
                message: 'token is required'
            });
            return;
        }

        // Use existing introspection function
        const validationResult = await introspectToken(token);

        res.json({
            success: true,
            message: 'Token validation completed',
            data: validationResult
        });

    } catch (error) {
        console.error('Token validation error:', (error as Error).message);
        res.status(500).json({
            error: 'Token validation failed',
            message: (error as Error).message
        });
    }
});

// Service info endpoint
app.get('/api/service-info', (req: Request, res: Response) => {
    res.json({
        introspection_service: {
            client_id: introspectionCredentials?.clientId,
            key_id: introspectionCredentials?.keyId,
            type: 'api_grants'
        },
        service_user: {
            user_id: serviceUserCredentials?.userId,
            client_id: serviceUserCredentials?.clientId,
            key_id: serviceUserCredentials?.keyId,
            type: 'service_account'
        },
        zitadel_domain: ZITADEL_DOMAIN,
        project_id: PROJECT_ID,
        token_endpoint: `${ZITADEL_DOMAIN}/oauth/v2/token`,
        introspection_endpoint: `${ZITADEL_DOMAIN}/oauth/v2/introspect`
    });
});

// ZITADEL API Access Functions

// Generate service user token for ZITADEL API access
async function getZitadelAPIToken(): Promise<string> {
    if (!serviceUserCredentials) {
        throw new Error('Service user credentials not loaded');
    }

    const now = Math.floor(Date.now() / 1000);

    // Generate JWT assertion for ZITADEL API access
    const jwtAssertion = jwt.sign({
        iss: serviceUserCredentials.clientId,
        sub: serviceUserCredentials.clientId,
        aud: ZITADEL_DOMAIN,
        exp: now + 300, // Expires in 5 minutes
        iat: now,
    }, serviceUserCredentials.key, {
        algorithm: 'RS256',
        keyid: serviceUserCredentials.keyId
    });

    // Exchange JWT for access token with ZITADEL API scope
    const tokenEndpoint = `${ZITADEL_DOMAIN}/oauth/v2/token`;
    const scopes = 'openid profile urn:zitadel:iam:org:project:id:zitadel:aud';

    const response = await axios.post(tokenEndpoint, {
        grant_type: 'urn:ietf:params:oauth:grant-type:jwt-bearer',
        assertion: jwtAssertion,
        scope: scopes
    }, {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    });

    return response.data.access_token;
}

// Sample endpoint to access ZITADEL Management API
app.get('/api/zitadel/org/me', async (req: Request, res: Response): Promise<void> => {
    try {
        // Get access token for ZITADEL API
        const accessToken = await getZitadelAPIToken();

        // Make request to ZITADEL Management API
        const response = await axios.get(`${ZITADEL_DOMAIN}/management/v1/orgs/me`, {
            headers: {
                'Authorization': `Bearer ${accessToken}`,
                'Content-Type': 'application/json'
            }
        });

        res.json({
            success: true,
            message: 'Organization data retrieved successfully',
            data: response.data
        });

    } catch (error) {
        console.error('ZITADEL API access error:', error);
        if (axios.isAxiosError(error) && error.response) {
            res.status(error.response.status).json({
                error: 'ZITADEL API access failed',
                message: error.response.data || error.message,
                status: error.response.status
            });
        } else {
            res.status(500).json({
                error: 'ZITADEL API access failed',
                message: (error as Error).message
            });
        }
    }
});

// Error handling middleware
app.use((error: Error, req: Request, res: Response, next: NextFunction) => {
    console.error('Unhandled error:', error);
    res.status(500).json({
        error: 'Internal server error',
        message: 'Something went wrong'
    });
});

// 404 handler
app.use((req: Request, res: Response) => {
    res.status(404).json({
        error: 'Not found',
        message: 'The requested endpoint does not exist'
    });
});

// Start server
app.listen(PORT, () => {
    console.log('\n🚀 Zitadel POC Server Started');
    console.log(`📍 Server URL: http://localhost:${PORT}`);
    console.log(`🌍 Zitadel Domain: ${ZITADEL_DOMAIN}`);
    console.log(`🆔 Project ID: ${PROJECT_ID}`);
    console.log('\n🔐 Service Users:');
    console.log(`   � Introspection Client ID: ${introspectionCredentials?.clientId}`);
    console.log(`   👤 Service User ID: ${serviceUserCredentials?.userId}`);
    console.log('\n📡 Available Endpoints:');
    console.log('   GET  /health - Health check');
    console.log('   POST /zitadel-poc/auth/store-tokens - Store auth tokens');
    console.log('   POST /zitadel-poc/auth/logout - Logout user');
    console.log('   GET  /zitadel-poc/user/dashboard - Get dashboard data');
    console.log('   GET  /zitadel-poc/test - Test protected endpoint');
    console.log('   POST /api/generate-token - Generate service user token');
    console.log('   POST /api/validate-token - Validate token via introspection');
    console.log('   GET  /api/service-info - Get service information');
    console.log('   GET  /api/zitadel/org/me - Get organization info via ZITADEL API');
    console.log('   GET  /api/zitadel/org/me - Get organization data from ZITADEL API');
    console.log('\n🔐 Authentication:');
    console.log('   🔍 Token Introspection: JWT client assertion with API grants');
    console.log('   🤖 Service User Access: JWT client assertion with ZITADEL API scope');
    console.log('📄 Documentation: https://zitadel.com/docs/guides/integrate/zitadel-apis/access-zitadel-apis');
    console.log('✅ Server ready!\n');
});

export default app;
