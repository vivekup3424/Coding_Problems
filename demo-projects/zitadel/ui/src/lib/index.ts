// place files you want to import through the `$lib` alias in this folder.
export const DOMAIN = "https://auth.keus.in";
export const CLIENT_ID = "327213041626185734"; // stage
// export const CLIENT_ID = "332278888744943622"; // dev
export const REDIRECT_URI = "http://localhost:3000/auth/callback";
export const POST_LOGOUT_REDIRECT_URI = "http://localhost:3000/auth/logged-out";

// Authentication state management
export interface AuthState {
    codeVerifier: string;
    codeChallenge: string;
    state: string;
}

export interface TokenResponse {
    access_token: string;
    id_token: string;
    refresh_token?: string;
    token_type: string;
    expires_in: number;
}

export interface UserInfo {
    sub: string;
    email?: string;
    email_verified?: boolean;
    name?: string;
    given_name?: string;
    family_name?: string;
    preferred_username?: string;
    picture?: string;
}

// Generate cryptographically secure random string
function generateRandomString(length: number): string {
    const charset = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~';
    let result = '';
    const randomValues = new Uint8Array(length);
    crypto.getRandomValues(randomValues);

    for (let i = 0; i < length; i++) {
        result += charset.charAt(randomValues[i] % charset.length);
    }
    return result;
}

// SHA256 hash function
async function sha256(plain: string): Promise<ArrayBuffer> {
    const encoder = new TextEncoder();
    const data = encoder.encode(plain);
    return await crypto.subtle.digest('SHA-256', data);
}

// Base64URL encode function
function base64URLEncode(buffer: ArrayBuffer): string {
    const bytes = new Uint8Array(buffer);
    let binary = '';
    for (let i = 0; i < bytes.byteLength; i++) {
        binary += String.fromCharCode(bytes[i]);
    }
    return btoa(binary)
        .replace(/\+/g, '-')
        .replace(/\//g, '_')
        .replace(/=/g, '');
}

// Generate PKCE parameters
export async function generatePKCE(): Promise<AuthState> {
    // Generate code verifier (random string between 43-128 chars)
    const codeVerifier = generateRandomString(128);

    // Generate code challenge (SHA256 hash of verifier, base64url encoded)
    const hashedVerifier = await sha256(codeVerifier);
    const codeChallenge = base64URLEncode(hashedVerifier);

    // Generate state parameter for CSRF protection
    const state = generateRandomString(32);

    return {
        codeVerifier,
        codeChallenge,
        state
    };
}

// Store auth state in localStorage
export function storeAuthState(authState: AuthState): void {
    localStorage.setItem('auth_state', JSON.stringify(authState));
}

// Retrieve auth state from localStorage
export function getAuthState(): AuthState | null {
    const stored = localStorage.getItem('auth_state');
    return stored ? JSON.parse(stored) : null;
}

// Clear auth state from localStorage
export function clearAuthState(): void {
    localStorage.removeItem('auth_state');
}

// Generate authorization URL
export function generateAuthorizationUrl(authState: AuthState): string {
    const params = new URLSearchParams({
        client_id: CLIENT_ID,
        redirect_uri: REDIRECT_URI,
        response_type: 'code',
        scope: 'openid profile email offline_access',
        code_challenge: authState.codeChallenge,
        code_challenge_method: 'S256',
        state: authState.state
    });

    return `${DOMAIN}/oauth/v2/authorize?${params.toString()}`;
}

// Exchange authorization code for tokens
export async function exchangeCodeForTokens(code: string, codeVerifier: string): Promise<TokenResponse> {
    const tokenData = new URLSearchParams({
        grant_type: 'authorization_code',
        code: code,
        redirect_uri: REDIRECT_URI,
        client_id: CLIENT_ID,
        code_verifier: codeVerifier
    });

    const response = await fetch(`${DOMAIN}/oauth/v2/token`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: tokenData
    });

    if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Token exchange failed: ${response.status} ${errorText}`);
    }

    return await response.json();
}

// Get user info from token
export async function getUserInfo(accessToken: string): Promise<UserInfo> {
    const response = await fetch(`${DOMAIN}/oidc/v1/userinfo`, {
        headers: {
            'Authorization': `Bearer ${accessToken}`
        }
    });

    if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Failed to get user info: ${response.status} ${errorText}`);
    }

    return await response.json();
}

// Store tokens in localStorage
export function storeTokens(tokens: TokenResponse): void {
    localStorage.setItem('auth_tokens', JSON.stringify(tokens));
}

// Retrieve tokens from localStorage
export function getTokens(): TokenResponse | null {
    const stored = localStorage.getItem('auth_tokens');
    return stored ? JSON.parse(stored) : null;
}

// Clear tokens from localStorage
export function clearTokens(): void {
    localStorage.removeItem('auth_tokens');
}

// Store user info in localStorage
export function storeUserInfo(userInfo: UserInfo): void {
    localStorage.setItem('user_info', JSON.stringify(userInfo));
}

// Retrieve user info from localStorage
export function getUserInfoFromStorage(): UserInfo | null {
    const stored = localStorage.getItem('user_info');
    return stored ? JSON.parse(stored) : null;
}

// Clear user info from localStorage
export function clearUserInfo(): void {
    localStorage.removeItem('user_info');
}

// JWT token validation utilities
function base64UrlDecode(str: string): string {
    // Add padding if needed
    const padding = '='.repeat((4 - str.length % 4) % 4);
    const base64 = str.replace(/-/g, '+').replace(/_/g, '/') + padding;

    try {
        return atob(base64);
    } catch (error) {
        throw new Error('Invalid base64url string');
    }
}

function decodeJWT(token: string): any {
    try {
        const parts = token.split('.');
        if (parts.length !== 3) {
            throw new Error('Invalid JWT format');
        }

        const payload = base64UrlDecode(parts[1]);
        return JSON.parse(payload);
    } catch (error) {
        throw new Error('Failed to decode JWT token');
    }
}

function isTokenExpired(token: string): boolean {
    try {
        const decoded = decodeJWT(token);
        const now = Math.floor(Date.now() / 1000);
        return decoded.exp && decoded.exp < now;
    } catch (error) {
        console.error('Error checking token expiration:', error);
        return true; // Consider invalid tokens as expired
    }
}

// Check if user is authenticated
export function isAuthenticated(): boolean {
    const tokens = getTokens();
    console.log("tokens", tokens)
    if (!tokens) return false;

    // Check if access token is expired
    if (isTokenExpired(tokens.access_token)) {
        console.log('Access token is expired');
        // Clear expired tokens
        clearTokens();
        clearUserInfo();
        return false;
    }

    return true;
}

// Get token expiration info
export function getTokenExpirationInfo(token: string): { exp: number, isExpired: boolean } | null {
    try {
        const decoded = decodeJWT(token);
        const now = Math.floor(Date.now() / 1000);
        return {
            exp: decoded.exp || 0,
            isExpired: decoded.exp ? decoded.exp < now : false
        };
    } catch (error) {
        return null;
    }
}

// Generate logout URL
export function generateLogoutUrl(idToken?: string): string {
    const params = new URLSearchParams({
        post_logout_redirect_uri: POST_LOGOUT_REDIRECT_URI
    });

    if (idToken) {
        params.set('id_token_hint', idToken);
    } else {
        params.set('client_id', CLIENT_ID);
    }

    return `${DOMAIN}/oidc/v1/end_session?${params.toString()}`;
}

// Complete logout process
export function logout(idToken?: string): void {
    // Clear local storage
    clearAuthState();
    clearTokens();
    clearUserInfo();

    // Redirect to logout URL
    const logoutUrl = generateLogoutUrl(idToken);
    window.location.href = logoutUrl;
}

// Refresh access token using refresh token
export async function refreshAccessToken(refreshToken: string): Promise<TokenResponse> {
    const tokenData = new URLSearchParams({
        grant_type: 'refresh_token',
        refresh_token: refreshToken,
        client_id: CLIENT_ID
    });

    const response = await fetch(`${DOMAIN}/oauth/v2/token`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: tokenData
    });

    if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Token refresh failed: ${response.status} ${errorText}`);
    }

    return await response.json();
}

// Auto-refresh tokens if needed
export async function ensureValidTokens(): Promise<TokenResponse | null> {
    const tokens = getTokens();
    if (!tokens) return null;

    // Check if access token is expired
    if (isTokenExpired(tokens.access_token)) {
        console.log('Access token expired, attempting refresh...');

        if (tokens.refresh_token && !isTokenExpired(tokens.refresh_token)) {
            try {
                const newTokens = await refreshAccessToken(tokens.refresh_token);
                storeTokens(newTokens);
                console.log('Tokens refreshed successfully');
                return newTokens;
            } catch (error) {
                console.error('Failed to refresh tokens:', error);
                // Clear invalid tokens
                clearTokens();
                clearUserInfo();
                return null;
            }
        } else {
            console.log('No valid refresh token available');
            // Clear expired tokens
            clearTokens();
            clearUserInfo();
            return null;
        }
    }

    return tokens;
}

// API client configuration
// const API_BASE_URL = 'http://localhost:3003';
const API_BASE_URL = 'http://heimdall.keus.in';

// API client functions
export async function callProtectedAPI(endpoint: string, options: RequestInit = {}): Promise<any> {
    try {
        const tokens = await ensureValidTokens();

        if (!tokens) {
            throw new Error('No valid tokens available. Please login again.');
        }

        const response = await fetch(`${API_BASE_URL}${endpoint}`, {
            ...options,
            credentials: 'include', // Include cookies in requests
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${tokens.access_token}`,
                ...options.headers,
            },
        });

        if (!response.ok) {
            const errorData = await response.json().catch(() => ({}));
            throw new Error(errorData.message || `API call failed: ${response.status}`);
        }

        return await response.json();
    } catch (error) {
        console.error('API call failed:', error);
        throw error;
    }
}

// Store tokens in server session
export async function storeTokensInSession(tokens: TokenResponse, userInfo: UserInfo): Promise<void> {
    try {
        const response = await fetch(`${API_BASE_URL}/zitadel-poc/auth/store-tokens`, {
            method: 'POST',
            credentials: 'include',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ tokens, userInfo }),
        });

        if (!response.ok) {
            const errorData = await response.json().catch(() => ({}));
            throw new Error(errorData.message || 'Failed to store tokens in session');
        }
    } catch (error) {
        console.error('Failed to store tokens in session:', error);
        throw error;
    }
}

// Test protected API endpoint
export async function testProtectedAPI(): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/test');
}

// Get user profile from API
export async function getUserProfile(): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/user/profile');
}

// Get user dashboard data from API
export async function getUserDashboard(): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/user/dashboard');
}

// Get user settings from API
export async function getUserSettings(): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/user/settings');
}

// Update user profile via API
export async function updateUserProfile(updates: any): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/user/profile', {
        method: 'PUT',
        body: JSON.stringify(updates),
    });
}

// Update site information via API
export async function updateSite(siteId: string, address: string): Promise<any> {
    return await callProtectedAPI('/zitadel-poc/site/update_site', {
        method: 'POST',
        body: JSON.stringify({
            siteId,
            address
        }),
    });
}

// Logout via API
export async function logoutFromAPI(): Promise<void> {
    try {
        await fetch(`${API_BASE_URL}/zitadel-poc/auth/logout`, {
            method: 'POST',
            credentials: 'include',
        });
    } catch (error) {
        console.error('Failed to logout from API:', error);
    }
}