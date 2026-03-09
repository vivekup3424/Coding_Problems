# Zitadel POC Server

This is a Node.js/Express server that provides protected APIs using Zitadel for authentication.

## Features

- 🔐 JWT token introspection with Zitadel
- 🍪 Cookie-based session management
- 🛡️ Protected API endpoints
- 📊 User profile and dashboard APIs
- 🔄 Token validation middleware

## API Endpoints

### Authentication
- `POST /zitadel-poc/auth/store-tokens` - Store tokens in server session
- `POST /zitadel-poc/auth/logout` - Logout and clear session

### Protected APIs (require authentication)
- `GET /zitadel-poc/test` - Test protected API connectivity
- `GET /zitadel-poc/user/profile` - Get user profile
- `GET /zitadel-poc/user/dashboard` - Get user dashboard data
- `GET /zitadel-poc/user/settings` - Get user settings
- `PUT /zitadel-poc/user/profile` - Update user profile

### Health Check
- `GET /health` - Server health check

## Configuration

The server uses the following Zitadel configuration:
- **Domain**: `https://auth.keus.in`
- **Client ID**: `327213041626185734`
- **Port**: `8080`

## Token Validation

The server validates tokens using two methods:

1. **Token Introspection**: Calls Zitadel's `/oauth/v2/introspect` endpoint
2. **JWT Decoding**: Validates token structure and expiration

## Authentication Flow

1. User logs in through the Svelte frontend
2. Frontend calls `/zitadel-poc/auth/store-tokens` to store tokens in session
3. Subsequent API calls use the stored tokens for authentication
4. Server validates tokens with Zitadel before processing requests

## Getting Started

1. Install dependencies:
   ```bash
   cd server
   bun install
   ```

2. Start the server:
   ```bash
   bun run dev
   ```

3. Server will be available at `http://localhost:8080`

## CORS Configuration

The server is configured to accept requests from:
- `http://localhost:3000` (Svelte frontend)

## Error Handling

All endpoints return consistent error responses:
```json
{
  "error": "error_type",
  "message": "Human readable error message"
}
```

## Security Features

- Token introspection with Zitadel
- Session-based authentication
- CORS protection
- Input validation
- Error handling middlewarestall dependencies:

```bash
bun install
```

To run:

```bash
bun run index.ts
```

This project was created using `bun init` in bun v1.2.7. [Bun](https://bun.sh) is a fast all-in-one JavaScript runtime.
