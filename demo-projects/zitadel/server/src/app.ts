import express from 'express';
import session from 'express-session';
import jwt from 'jsonwebtoken';
import { v4 as uuidv4 } from 'uuid';
import fs from 'fs';
import crypto from 'crypto';

const app = express();
app.use(express.json());

// Add this after your imports
interface TokenIntrospectionResponse {
    active: boolean;
    sub?: string;
    iss?: string;
    exp?: number;
    iat?: number;
    username?: string;
    email?: string;
    scope?: string;
    client_id?: string;
    token_type?: string;
}

// Token validation middleware
async function validateToken(req: any, res: any, next: any) {
    const authHeader = req.headers.authorization || req.session.tokens?.access_token ? `Bearer ${req.session.tokens.access_token}` : null;

    console.log("sessiong - ", req.session.tokens);

    if (!authHeader || !authHeader.startsWith('Bearer ')) {
        return res.status(401).json({
            error: 'unauthorized',
            message: 'Missing or invalid authorization header'
        });
    }

    const token = authHeader.substring(7); // Remove 'Bearer ' prefix

    try {
        const isValid = await introspectToken(token);
        if (isValid.active) {
            req.user = isValid; // Store user info in request
            next();
        } else {
            return res.status(401).json({
                error: 'unauthorized',
                message: 'Token is not active'
            });
        }
    } catch (error: any) {
        console.error('❌ Token validation error:', error.message);
        return res.status(401).json({
            error: 'unauthorized',
            message: 'Token validation failed'
        });
    }
}

// Token introspection function using JWT Profile (recommended)
async function introspectToken(token: string): Promise<TokenIntrospectionResponse> {
    try {
        // Create client assertion for authentication with Zitadel
        const clientAssertion = createClientAssertion();

        const introspectionData = new URLSearchParams({
            client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer',
            client_assertion: clientAssertion,
            token: token
        });

        const response = await fetch(`${ZITADEL_DOMAIN}/oauth/v2/introspect`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
            },
            body: introspectionData
        });

        if (!response.ok) {
            const errorText = await response.text();
            throw new Error(`Introspection failed: ${response.status} ${errorText}`);
        }

        const tokenData = <TokenIntrospectionResponse>await response.json();

        console.log('✅ Token introspection result:', {
            active: tokenData.active,
            sub: tokenData.sub,
            exp: tokenData.exp ? new Date(tokenData.exp * 1000).toISOString() : 'N/A'
        });

        return tokenData;
    } catch (error: any) {
        console.error('❌ Token introspection error:', error.message);
        throw error;
    }
}

// Configure session middleware
app.use(session({
    secret: process.env.SESSION_SECRET || 'your-secret-key-change-in-production',
    resave: false,
    saveUninitialized: false,
    cookie: {
        secure: false, // Set to true in production with HTTPS
        maxAge: 1000 * 60 * 10 // 10 minutes
    }
}));

// ===========================
// CONSTANTS - Configure these
// ===========================
const ZITADEL_DOMAIN = "https://auth.keus.in";
const CLIENT_ID = "325033819512045574";
const REDIRECT_URI = "http://localhost:3000/auth/callback";
const POST_LOGOUT_REDIRECT_URI = "http://localhost:3000/auth/logged-out";
const PRIVATE_KEY_PATH = "./keys/key.json"; // Path to your private key file
const PORT = process.env.PORT || 3000;

// Derived URLs from constants
const AUTHORIZATION_ENDPOINT = `${ZITADEL_DOMAIN}/oauth/v2/authorize`;
const TOKEN_ENDPOINT = `${ZITADEL_DOMAIN}/oauth/v2/token`;
const USERINFO_ENDPOINT = `${ZITADEL_DOMAIN}/oidc/v1/userinfo`;
const END_SESSION_ENDPOINT = `${ZITADEL_DOMAIN}/oidc/v1/end_session`;

// ===========================
// UTILITY FUNCTIONS
// ===========================

// Generate cryptographically secure random string
function generateRandomString(length: number) {
    return crypto.randomBytes(length).toString('base64url');
}

// Load private key from file
function loadPrivateKey() {
    try {
        const keyData = fs.readFileSync(PRIVATE_KEY_PATH, 'utf8');
        const keyJson = JSON.parse(keyData);
        return keyJson.key;
    } catch (error: any) {
        console.error('❌ Error loading private key:', error.message);
        console.log('💡 Make sure the key.json file contains a valid private key in the "key" field');
        process.exit(1);
    }
}

// Create JWT client assertion
function createClientAssertion() {
    const privateKey = loadPrivateKey();
    const keyData = JSON.parse(fs.readFileSync(PRIVATE_KEY_PATH, 'utf8'));
    const keyId = keyData.keyId;
    const now = Math.floor(Date.now() / 1000);

    const payload = {
        iss: CLIENT_ID,                    // Issuer: your client ID
        sub: CLIENT_ID,                    // Subject: your client ID
        aud: ZITADEL_DOMAIN,               // Audience: ZITADEL's domain (not token endpoint)
        jti: uuidv4(),                     // JWT ID: unique identifier
        exp: now + 300,                    // Expires: 5 minutes from now
        iat: now                           // Issued at: current time
    };

    // Sign JWT with RS256 algorithm, including key ID in header
    return jwt.sign(payload, privateKey, {
        algorithm: 'RS256',
        keyid: keyId
    });
}

// Exchange authorization code for tokens using JWT client assertion
async function exchangeCodeForTokens(authorizationCode: string) {
    const clientAssertion = createClientAssertion();
    console.log("🔄 Exchanging authorization code for tokens...")
    const tokenData = new URLSearchParams({
        grant_type: 'authorization_code',
        code: authorizationCode,
        redirect_uri: REDIRECT_URI,
        client_assertion: clientAssertion,
        client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer'
    });

    try {
        const response = await fetch(TOKEN_ENDPOINT, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded'
            },
            body: tokenData
        });

        if (!response.ok) {
            const errorText = await response.text();
            throw new Error(`Token exchange failed: ${response.status} ${errorText}`);
        }

        return await response.json();
    } catch (error: any) {
        console.error('❌ Token exchange error:', error.message);
        throw error;
    }
}

// Get user info using access token
async function getUserInfo(accessToken: string) {
    try {
        const response = await fetch(USERINFO_ENDPOINT, {
            headers: {
                'Authorization': `Bearer ${accessToken}`
            }
        });

        if (!response.ok) {
            throw new Error(`UserInfo request failed: ${response.status}`);
        }

        return await response.json();
    } catch (error: any) {
        console.error('❌ UserInfo error:', error.message);
        throw error;
    }
}

// ===========================
// ROUTES
// ===========================

// Home page - start login
app.get('/', (req, res) => {
    // Check if user is already logged in
    if (req.session.tokens && req.session.userInfo) {
        const userInfo = req.session.userInfo;
        const tokens = req.session.tokens;

        res.send(`
            <!DOCTYPE html>
            <html>
            <head>
                <title>JWT Client Assertion Demo - Dashboard</title>
                <style>
                    body { font-family: Arial, sans-serif; max-width: 800px; margin: 50px auto; padding: 20px; }
                    .btn { background: #4f46e5; color: white; padding: 12px 24px; text-decoration: none; border-radius: 6px; display: inline-block; margin: 10px 10px 10px 0; }
                    .btn:hover { background: #4338ca; }
                    .logout-btn { background: #dc2626; color: white; padding: 12px 24px; text-decoration: none; border-radius: 6px; display: inline-block; margin: 10px 10px 10px 0; }
                    .logout-btn:hover { background: #b91c1c; }
                    .info { background: #dbeafe; padding: 15px; border-radius: 6px; margin: 20px 0; }
                    .user-info { background: #d1fae5; padding: 15px; border-radius: 6px; margin: 20px 0; }
                    .code { background: #f3f4f6; padding: 10px; border-radius: 4px; font-family: monospace; margin: 10px 0; }
                </style>
            </head>
            <body>
                <h1>🔐 JWT Client Assertion Demo - Dashboard</h1>
                
                <div class="user-info">
                    <h3>👤 Welcome back!</h3>
                    <p><strong>Name:</strong> ${userInfo.name || 'N/A'}</p>
                    <p><strong>Email:</strong> ${userInfo.email || 'N/A'}</p>
                    <p><strong>Subject:</strong> ${userInfo.sub}</p>
                    <p><strong>Login Status:</strong> ✅ Authenticated</p>
                </div>
                
                <div class="info">
                    <strong>Session Information:</strong><br>
                    <p>You are currently logged in with a valid session.</p>
                    <p>Your tokens are stored securely in the server session.</p>
                </div>
                
                <div style="margin-top: 20px;">
                    <a href="/auth/logout" class="logout-btn">🚪 Logout</a>
                    <a href="/health" class="btn">🏥 System Health</a>
                    <a href="/api/me" class="btn">🔒 Protected API</a>
                    <a href="/debug/tokens" class="btn">🔑 Get Tokens</a>
                </div>
                
                <h3>📋 Available Actions:</h3>
                <ul>
                    <li><strong>Logout:</strong> Terminate your session with ZITADEL</li>
                    <li><strong>Health Check:</strong> View application configuration</li>
                    <li><strong>Protected API:</strong> Test protected endpoint (requires valid token)</li>
                    <li><strong>Get Tokens:</strong> Retrieve access token for API testing</li>
                </ul>
            </body>
            </html>
        `);
        return;
    }

    // User is not logged in, show login page
    const state = generateRandomString(32);
    const nonce = generateRandomString(32);

    // Store state and nonce in session
    req.session.state = state;
    req.session.nonce = nonce;

    const authParams = new URLSearchParams({
        client_id: CLIENT_ID,
        redirect_uri: REDIRECT_URI,
        response_type: 'code',
        scope: 'openid profile email phone offline_access',
        state: state,
        nonce: nonce
    });

    const authUrl = `${AUTHORIZATION_ENDPOINT}?${authParams}`;

    res.send(`
        <!DOCTYPE html>
        <html>
        <head>
            <title>JWT Client Assertion Demo</title>
            <style>
                body { font-family: Arial, sans-serif; max-width: 800px; margin: 50px auto; padding: 20px; }
                .btn { background: #4f46e5; color: white; padding: 12px 24px; text-decoration: none; border-radius: 6px; display: inline-block; }
                .btn:hover { background: #4338ca; }
                .info { background: #dbeafe; padding: 15px; border-radius: 6px; margin: 20px 0; }
                .code { background: #f3f4f6; padding: 10px; border-radius: 4px; font-family: monospace; margin: 10px 0; }
            </style>
        </head>
        <body>
            <h1>🔐 JWT Client Assertion Demo</h1>
            
            <div class="info">
                <strong>Configuration:</strong><br>
                <div class="code">Domain: ${ZITADEL_DOMAIN}</div>
                <div class="code">Client ID: ${CLIENT_ID}</div>
                <div class="code">Redirect URI: ${REDIRECT_URI}</div>
                <div class="code">Post Logout URI: ${POST_LOGOUT_REDIRECT_URI}</div>
            </div>
            
            <div class="info">
                <strong>Flow:</strong> Authorization Code with JWT Client Assertion<br>
                This uses private key cryptography instead of client secrets.
            </div>
            
            <a href="${authUrl}" class="btn">🚀 Login with ZITADEL</a>
            
            <h3>📋 Setup Instructions:</h3>
            <ol>
                <li>Generate a private key: <code>openssl genrsa -out private_key.pem 2048</code></li>
                <li>Extract public key: <code>openssl rsa -in private_key.pem -pubout -out public_key.pem</code></li>
                <li>Upload the public key to your ZITADEL application</li>
                <li>Set authentication method to "JWT with Private Key"</li>
                <li><strong>Configure post-logout redirect URI in ZITADEL Console:</strong>
                    <div class="code">${POST_LOGOUT_REDIRECT_URI}</div>
                    <em>Without this, logout will show a ZITADEL error page</em>
                </li>
            </ol>
            
            <h3>🔄 Logout Flow:</h3>
            <p>This application implements ZITADEL's RP initiated logout flow:</p>
            <ul>
                <li>Uses the <code>end_session_endpoint</code> for logout</li>
                <li>Includes <code>id_token_hint</code> for session identification</li>
                <li>Clears local application session</li>
                <li>Redirects to ZITADEL for complete logout</li>
            </ul>
        </body>
        </html>
    `);
});

// OAuth callback - handle authorization code
app.get('/auth/callback', async (req, res) => {
    const { code, state, error, error_description } = req.query;

    // Handle OAuth errors
    if (error) {
        res.status(400).send(`
            <h1>❌ Authorization Error</h1>
            <p><strong>Error:</strong> ${error}</p>
            <p><strong>Description:</strong> ${error_description || 'No description provided'}</p>
            <a href="/">← Back to Home</a>
        `);
        return;
    }

    // Check for authorization code
    if (!code) {
        res.status(400).send(`
            <h1>❌ Missing Authorization Code</h1>
            <p>No authorization code received from ZITADEL</p>
            <a href="/">← Back to Home</a>
        `);
        return;
    }

    console.log("origin - ", req.host, req.session.state, req.session.nonce)
    // Verify state parameter (CSRF protection)
    if (state !== req.session.state) {
        res.status(400).send(`
            <h1>❌ State Verification Failed</h1>
            <p>Possible CSRF attack detected</p>
            <a href="/">← Back to Home</a>
        `);
        return;
    }

    try {
        // Exchange authorization code for tokens using JWT client assertion
        console.log('🔄 Exchanging authorization code for tokens...');
        const tokens: any = await exchangeCodeForTokens(<string>code);

        console.log('✅ Tokens received:', tokens);

        // Store tokens in session
        req.session.tokens = {
            access_token: tokens.access_token,
            id_token: tokens.id_token,
            refresh_token: tokens.refresh_token
        };

        // Get user information
        console.log('🔄 Fetching user info...');
        const userInfo: any = await getUserInfo(tokens.access_token);

        // Store user info in session
        req.session.userInfo = userInfo;

        console.log('✅ User info received:', userInfo);

        // Display success page
        res.redirect('/');

    } catch (error: any) {
        console.error('❌ OAuth flow error:', error);
        res.status(500).send(`
            <h1>❌ Token Exchange Failed</h1>
            <p><strong>Error:</strong> ${error.message}</p>
            <a href="/">← Back to Home</a>
        `);
    }
});

// Logout route - redirect to ZITADEL end_session endpoint
app.get('/auth/logout', (req, res) => {
    const idToken = req.session.tokens?.id_token;
    const state = generateRandomString(32);

    // Clear session data
    req.session.destroy((err) => {
        if (err) {
            console.error('❌ Error destroying session:', err);
        }
    });

    // Build logout URL with post_logout_redirect_uri
    // Note: This will only work if you've configured the post-logout redirect URI in ZITADEL Console
    const logoutParams = new URLSearchParams({
        id_token_hint: idToken || '',
        post_logout_redirect_uri: POST_LOGOUT_REDIRECT_URI,
        client_id: CLIENT_ID,
        state: state
    });

    const logoutUrl = `${END_SESSION_ENDPOINT}?${logoutParams}`;

    console.log('🔄 Redirecting to logout URL:', logoutUrl);
    console.log('📝 If you see an error, configure the post-logout redirect URI in ZITADEL Console');
    res.redirect(logoutUrl);
});

// Manual logout completion page (for when post_logout_redirect_uri is not configured)
app.get('/auth/logged-out', (req, res) => {
    const { state } = req.query;

    console.log('✅ User accessed logout completion page');

    res.send(`
        <!DOCTYPE html>
        <html>
        <head>
            <title>Logged Out</title>
            <style>
                body { font-family: Arial, sans-serif; max-width: 800px; margin: 50px auto; padding: 20px; }
                .success { background: #d1fae5; border: 1px solid #34d399; padding: 15px; border-radius: 6px; color: #065f46; }
                .info { background: #dbeafe; padding: 15px; border-radius: 6px; margin: 20px 0; }
                .warning { background: #fef3c7; border: 1px solid #f59e0b; padding: 15px; border-radius: 6px; color: #92400e; margin: 20px 0; }
                .btn { background: #4f46e5; color: white; padding: 12px 24px; text-decoration: none; border-radius: 6px; display: inline-block; }
                .btn:hover { background: #4338ca; }
                .code { background: #f3f4f6; padding: 10px; border-radius: 4px; font-family: monospace; margin: 10px 0; }
            </style>
        </head>
        <body>
            <div class="success">
                <h1>✅ Logout Process Completed!</h1>
                <p>Your local session has been terminated.</p>
            </div>
            
            <div class="warning">
                <h3>⚠️ ZITADEL Configuration Required</h3>
                <p>To enable automatic redirect after logout, please configure the following in your ZITADEL Console:</p>
                <ol>
                    <li>Go to your ZITADEL Console</li>
                    <li>Navigate to your application settings</li>
                    <li>Add this post-logout redirect URI:</li>
                    <div class="code">${POST_LOGOUT_REDIRECT_URI}</div>
                    <li>Save the configuration</li>
                </ol>
                <p>After configuration, logout will automatically redirect users back to this page.</p>
            </div>
            
            <div class="info">
                <p>Your application session has been terminated. For complete logout from ZITADEL, please close your browser or visit ZITADEL directly.</p>
                <p>Thank you for using our JWT Client Assertion demo!</p>
            </div>
            
            <a href="/" class="btn">🔐 Login Again</a>
        </body>
        </html>
    `);
});

// Health check endpoint
app.get('/health', (req, res) => {
    res.json({
        status: 'healthy',
        timestamp: new Date().toISOString(),
        config: {
            domain: ZITADEL_DOMAIN,
            client_id: CLIENT_ID,
            redirect_uri: REDIRECT_URI,
            post_logout_redirect_uri: POST_LOGOUT_REDIRECT_URI,
            endpoints: {
                authorization: AUTHORIZATION_ENDPOINT,
                token: TOKEN_ENDPOINT,
                userinfo: USERINFO_ENDPOINT,
                end_session: END_SESSION_ENDPOINT
            }
        },
        session: {
            authenticated: !!req.session.tokens,
            user_present: !!req.session.userInfo
        }
    });
});

// Token info endpoint - shows current user info from token
app.get('/api/me', validateToken, (req, res) => {

    res.json({
        //@ts-ignore
        user: req.user,
        message: 'Token is valid and active'
    });
});

// Debug endpoint to get current session tokens (for testing protected endpoints)
app.get('/debug/tokens', (req: any, res: any) => {
    if (!req.session.tokens) {
        return res.status(401).json({
            error: 'not_authenticated',
            message: 'No active session. Please log in first.',
            login_url: `http://localhost:${PORT}/`
        });
    }

    res.json({
        message: 'Current session tokens (for testing protected endpoints)',
        instructions: {
            usage: 'Use the access_token below in Authorization header',
            example: `curl -H "Authorization: Bearer YOUR_ACCESS_TOKEN" http://localhost:${PORT}/api/me`,
            note: 'These tokens expire. If you get 401 errors, log in again.'
        },
        tokens: {
            access_token: req.session.tokens.access_token,
            token_type: 'Bearer',
            // Don't expose refresh_token and id_token for security in real apps
            expires_info: 'Access tokens typically expire in 1 hour'
        },
        user_info: req.session.userInfo
    });
});

// ===========================
// START SERVER
// ===========================
app.listen(PORT, () => {
    console.log(`🚀 Server is running on http://localhost:${PORT}`);
    console.log(`📋 Configuration:`);
    console.log(`   - ZITADEL Domain: ${ZITADEL_DOMAIN}`);
    console.log(`   - Client ID: ${CLIENT_ID}`);
    console.log(`   - Redirect URI: ${REDIRECT_URI}`);
    console.log(`   - Post Logout URI: ${POST_LOGOUT_REDIRECT_URI}`);
    console.log(`   - Private Key: ${PRIVATE_KEY_PATH}`);
    console.log(`\n🔧 ZITADEL Setup Required:`);
    console.log(`   1. Generate private key: openssl genrsa -out private_key.pem 2048`);
    console.log(`   2. Extract public key: openssl rsa -in private_key.pem -pubout -out public_key.pem`);
    console.log(`   3. Upload public key to ZITADEL application`);
    console.log(`   4. Set authentication method to "JWT with Private Key"`);
    console.log(`   5. ⚠️  IMPORTANT: Add post-logout redirect URI in ZITADEL Console:`);
    console.log(`      ${POST_LOGOUT_REDIRECT_URI}`);
    console.log(`\n🌐 Endpoints:`);
    console.log(`   - Home: http://localhost:${PORT}`);
    console.log(`   - Callback: http://localhost:${PORT}/auth/callback`);
    console.log(`   - Logout: http://localhost:${PORT}/auth/logout`);
    console.log(`   - Post-logout: http://localhost:${PORT}/auth/logged-out`);
    console.log(`   - Health: http://localhost:${PORT}/health`);
    console.log(`   - Protected API: http://localhost:${PORT}/api/me (requires Bearer token)`);
    console.log(`   - Debug Tokens: http://localhost:${PORT}/debug/tokens (get tokens for testing)`);
});