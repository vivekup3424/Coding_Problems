// Shared types for the server
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

// JWT token interface
export interface DecodedToken {
    sub: string;
    email?: string;
    email_verified?: boolean;
    name?: string;
    given_name?: string;
    family_name?: string;
    preferred_username?: string;
    picture?: string;
    iss: string;
    aud: string;
    exp: number;
    iat: number;
    client_id?: string;
    site_id?: string; // Added site_id field
}

// Token response interface
export interface TokenResponse {
    access_token: string;
    id_token: string;
    refresh_token?: string;
    token_type: string;
    expires_in: number;
}
