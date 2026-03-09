import jwksClient from 'jwks-rsa';
import jwt from "jsonwebtoken";
import type { JwtHeader, JwtPayload } from "jsonwebtoken";
import { promisify } from 'util';

interface DecodedToken {
    header: JwtHeader;
    payload: JwtPayload;
    signature: string;
}

// Setup JWKS client
const client = jwksClient({
    jwksUri: 'https://auth.keus.in/oauth/v2/keys',
    cache: true,
    cacheMaxAge: 600000 // 10 minutes
});

// Convert jwt.verify to promise with proper typing
const jwtVerifyAsync = promisify(jwt.verify) as (
    token: string,
    secretOrPublicKey: string,
    options?: jwt.VerifyOptions
) => Promise<jwt.JwtPayload>;

// Async function to get signing key
async function getKey(kid: string): Promise<string> {
    try {
        const key = await client.getSigningKey(kid);

        if (!key) {
            throw new Error('No key found');
        }

        // Use getPublicKey() method instead of direct property access
        const signingKey = key.getPublicKey();

        if (!signingKey) {
            throw new Error('No signing key found in key object');
        }

        return signingKey;
    } catch (err) {
        console.error('JWKS Error:', err);
        throw err;
    }
}

// Token verification function with improved error handling
export const verifyToken = async (token: string): Promise<jwt.JwtPayload> => {
    try {
        if (!token) {
            throw new Error('Token is required');
        }

        // Decode token to get kid
        const decoded = jwt.decode(token, { complete: true }) as DecodedToken | null;

        if (!decoded) {
            throw new Error('Invalid token format');
        }

        const kid = decoded.header?.kid;

        if (!kid) {
            throw new Error('No kid in token header');
        }

        // Get signing key
        const signingKey = await getKey(kid);

        // Verify token with proper options
        const verified = await jwtVerifyAsync(token, signingKey, {
            audience: '327234963625803782',
            issuer: 'https://auth.keus.in',
            algorithms: ['RS256']
        });

        console.log("Token verification successful");
        console.log("Decoded token:", verified);

        return verified;

    } catch (err) {
        console.log("Token verification failed:", err);
        throw err;
    }
};