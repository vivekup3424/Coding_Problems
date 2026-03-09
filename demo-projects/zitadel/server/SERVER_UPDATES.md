# Server Update Documentation

## Changes Made

### 1. Service User Authentication for Token Introspection
- Added service user JWT generation using RSA private key
- Implemented service user token acquisition
- Updated token introspection to use service user authentication
- Added proper error handling for service user credential loading

### 2. API Cleanup and Simplification
- **Removed unused endpoints:**
  - `/zitadel-poc/user/dashboard` - Complex dashboard data endpoint
  - `/zitadel-poc/user/settings` - User settings endpoint  
  - `/zitadel-poc/user/profile` (PUT) - Profile update endpoint

- **Kept essential endpoints:**
  - `GET /api/user/profile` - Get user profile information
  - `POST /api/auth/store-tokens` - Store authentication tokens
  - `POST /api/auth/logout` - User logout
  - `GET /api/test` - API connectivity test
  - `GET /health` - Health check

### 3. Environment Configuration
- Added dotenv support for environment variables
- Created `.env` and `.env.example` files
- Configurable Zitadel domain, client ID, and session secret
- Environment-aware CORS and security settings

### 4. Security Improvements
- Service user authentication for token introspection
- Environment-aware session security (secure cookies in production)
- Flexible CORS configuration for development and production

## Required Environment Variables

```env
PORT=8080
ZITADEL_DOMAIN=https://auth.keus.in
CLIENT_ID=327213041626185734
SESSION_SECRET=your-session-secret-key-change-this-in-production
NODE_ENV=development
```

## API Endpoints for Svelte App

### Authentication
- `POST /zitadel-poc/auth/store-tokens` - Store tokens after login
- `POST /zitadel-poc/auth/logout` - Logout user

### User Data
- `GET /zitadel-poc/user/profile` - Get user profile (requires auth)
- `GET /zitadel-poc/user/dashboard` - Get dashboard data (requires auth)
- `GET /zitadel-poc/user/settings` - Get user settings (requires auth)
- `PUT /zitadel-poc/user/profile` - Update user profile (requires auth)

### Utility
- `GET /health` - Health check
- `GET /zitadel-poc/test` - Test protected API (requires auth)

## Service User Requirements

The server requires a `keys/key.json` file with service user credentials:
```json
{
    "type": "application",
    "keyId": "your-key-id",
    "key": "-----BEGIN RSA PRIVATE KEY-----\n...\n-----END RSA PRIVATE KEY-----\n",
    "appId": "your-app-id",
    "clientId": "your-client-id"
}
```

## CORS Configuration

- **Development:** Allows `localhost:3000` and `localhost:5173`
- **Production:** Configure allowed origins in environment
