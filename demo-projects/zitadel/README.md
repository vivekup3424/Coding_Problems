# Zitadel Authentication POC

This project demonstrates a complete authentication flow using Zitadel as the identity provider, with a Svelte frontend and Express.js backend.

## Project Structure

```
zitadel/
├── server/                 # Express.js backend
│   ├── src/
│   │   └── server.ts      # Main server file with protected APIs
│   ├── package.json
│   └── README.md
└── ui/                    # Svelte frontend
    ├── src/
    │   ├── lib/
    │   │   └── index.ts   # Authentication utilities
    │   └── routes/
    │       └── +page.svelte # Main page with login/logout
    ├── package.json
    └── README.md
```

## Features

### Frontend (Svelte)
- 🔐 OAuth 2.0 with PKCE flow
- 🍪 Token management (localStorage + server session)
- 🎨 Beautiful, responsive UI
- 🧪 API testing interface
- 🔄 Automatic token refresh

### Backend (Express.js)
- 🛡️ JWT token introspection with Zitadel
- 🍪 Session-based authentication
- 📊 Protected API endpoints
- 🔍 Token validation middleware
- 📝 Comprehensive error handling

## Quick Start

### 1. Start the Backend Server

```bash
cd server
bun install
bun run dev
```

Server will be available at `http://localhost:8080`

### 2. Start the Frontend

```bash
cd ui
npm install
npm run dev
```

Frontend will be available at `http://localhost:3001`

### 3. Test the Integration

1. Open `http://localhost:3001` in your browser
2. Click "Login with Zitadel"
3. Complete the authentication flow
4. Once logged in, test the protected APIs using the buttons

## API Endpoints

### Authentication
- `POST /zitadel-poc/auth/store-tokens` - Store tokens in server session
- `POST /zitadel-poc/auth/logout` - Logout and clear session

### Protected APIs
- `GET /zitadel-poc/test` - Test API connectivity
- `GET /zitadel-poc/user/profile` - Get user profile
- `GET /zitadel-poc/user/dashboard` - Get dashboard data
- `GET /zitadel-poc/user/settings` - Get user settings
- `PUT /zitadel-poc/user/profile` - Update user profile

## Configuration

### Zitadel Settings
- **Domain**: `https://auth.keus.in`
- **Client ID**: `327213041626185734`
- **Redirect URI**: `http://localhost:3001/auth/callback`
- **Post Logout URI**: `http://localhost:3001/auth/logged-out`

### Server Configuration
- **Port**: 8080
- **CORS**: Configured for `http://localhost:3001`
- **Session**: Cookie-based with secure settings

## Authentication Flow

1. **Login**: User clicks login → redirected to Zitadel
2. **Callback**: Zitadel redirects back with authorization code
3. **Token Exchange**: Frontend exchanges code for tokens
4. **Session Storage**: Tokens stored in both localStorage and server session
5. **API Calls**: Protected APIs validated via token introspection
6. **Logout**: Clears both client and server sessions

## Security Features

- ✅ PKCE (Proof Key for Code Exchange)
- ✅ State parameter for CSRF protection
- ✅ Token introspection with Zitadel
- ✅ Secure session management
- ✅ CORS protection
- ✅ Automatic token refresh
- ✅ Proper error handling

## Development

### Prerequisites
- Node.js 18+
- Bun runtime
- Zitadel instance configured

### Environment Variables
All configuration is currently hardcoded. In production, use environment variables:

```env
ZITADEL_DOMAIN=https://auth.keus.in
ZITADEL_CLIENT_ID=327213041626185734
FRONTEND_URL=http://localhost:3001
SESSION_SECRET=your-secret-key
```

### VS Code Tasks
The project includes VS Code tasks for easy development:
- `Start Zitadel Server` - Starts the backend server

## Testing

### Manual Testing
1. Use the frontend interface to login
2. Test protected APIs using the built-in buttons
3. Check browser developer tools for token/session details

### API Testing with curl
```bash
# Test health endpoint
curl http://localhost:8080/health

# Test protected endpoint (requires authentication)
curl -H "Authorization: Bearer YOUR_TOKEN" http://localhost:8080/zitadel-poc/test
```

## Troubleshooting

### Common Issues

1. **Port Conflicts**: If ports 3001 or 8080 are in use, update the configuration
2. **CORS Errors**: Ensure server CORS settings match frontend URL
3. **Token Validation**: Check Zitadel domain and client ID configuration
4. **Session Issues**: Clear browser cookies and localStorage

### Debug Mode
Enable debug logging by checking browser console and server logs.

## Production Considerations

- Use environment variables for configuration
- Enable HTTPS for all communications
- Implement proper logging and monitoring
- Add rate limiting and security headers
- Use secure session stores (Redis, etc.)
- Implement proper error boundaries
- Add health checks and monitoring
