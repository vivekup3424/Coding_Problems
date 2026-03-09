# Zitadel PKCE Authentication Demo

This project demonstrates a complete implementation of OAuth 2.0 with PKCE (Proof Key for Code Exchange) using Zitadel as the identity provider, built with SvelteKit and Bun.

## 🚀 Features

- **Secure PKCE Flow**: Implements RFC 7636 with proper code verifier/challenge generation
- **Token Management**: Automatic token refresh and expiration handling
- **User Info**: Retrieves and displays user profile information
- **Logout Handling**: Proper session termination with Zitadel
- **Error Handling**: Comprehensive error handling for all auth scenarios
- **Modern UI**: Clean, responsive design with real-time status updates

## 🛠️ Technology Stack

- **Frontend**: SvelteKit 5 with TypeScript
- **Runtime**: Bun
- **Identity Provider**: Zitadel
- **Authentication**: OAuth 2.0 with PKCE
- **Storage**: Browser localStorage for session management

## 📋 Prerequisites

- Bun installed on your system
- Zitadel instance configured (https://auth.keus.in)
- OAuth application configured in Zitadel

## 🔧 Configuration

Update the constants in `src/lib/index.ts`:

```typescript
export const DOMAIN = "https://auth.keus.in";
export const CLIENT_ID = "325033819512045574";
export const REDIRECT_URI = "http://localhost:3000/auth/callback";
export const POST_LOGOUT_REDIRECT_URI = "http://localhost:3000/auth/logged-out";
```

## 🚦 Getting Started

1. **Install dependencies**:
   ```bash
   bun install
   ```

2. **Start development server**:
   ```bash
   bun run dev
   ```

3. **Open browser**:
   Navigate to `http://localhost:3000`

## 📁 Project Structure

```
src/
├── lib/
│   └── index.ts          # Core authentication functions
├── routes/
│   ├── +page.svelte      # Main authentication page
│   ├── demo/
│   │   └── +page.svelte  # Token and user info demo
│   └── auth/
│       ├── callback/
│       │   └── +page.svelte  # OAuth callback handler
│       └── logged-out/
│           └── +page.svelte  # Post-logout page
```

## 🔐 Authentication Flow

### 1. Login Process

1. **Generate PKCE Parameters**:
   - Code verifier (128 characters, cryptographically random)
   - Code challenge (SHA256 hash of verifier, base64url encoded)
   - State parameter (32 characters, for CSRF protection)

2. **Authorization Request**:
   ```
   GET /oauth/v2/authorize?
     client_id=YOUR_CLIENT_ID&
     redirect_uri=http://localhost:3000/auth/callback&
     response_type=code&
     scope=openid profile email&
     code_challenge=CHALLENGE&
     code_challenge_method=S256&
     state=STATE
   ```

3. **Authorization Code Exchange**:
   ```
   POST /oauth/v2/token
   Content-Type: application/x-www-form-urlencoded
   
   grant_type=authorization_code&
   code=AUTHORIZATION_CODE&
   redirect_uri=http://localhost:3000/auth/callback&
   client_id=YOUR_CLIENT_ID&
   code_verifier=VERIFIER
   ```

4. **Token Response**:
   ```json
   {
     "access_token": "...",
     "id_token": "...",
     "refresh_token": "...",
     "token_type": "Bearer",
     "expires_in": 3600
   }
   ```

### 2. Token Management

- **Automatic Validation**: JWT tokens are decoded and checked for expiration
- **Refresh Handling**: Automatic token refresh using refresh tokens
- **Storage**: Secure storage in localStorage with proper cleanup

### 3. Logout Process

1. **Clear Local Storage**: Remove all stored tokens and user info
2. **Redirect to End Session**: 
   ```
   GET /oidc/v1/end_session?
     id_token_hint=ID_TOKEN&
     post_logout_redirect_uri=http://localhost:3000/auth/logged-out
   ```

## 🔑 Key Functions

### Authentication State Management

```typescript
// Generate PKCE parameters
const authState = await generatePKCE();

// Store auth state for callback
storeAuthState(authState);

// Generate authorization URL
const authUrl = generateAuthorizationUrl(authState);
```

### Token Exchange

```typescript
// Exchange code for tokens
const tokens = await exchangeCodeForTokens(code, codeVerifier);

// Store tokens
storeTokens(tokens);

// Get user info
const userInfo = await getUserInfo(tokens.access_token);
```

### Token Validation

```typescript
// Check if authenticated
const isLoggedIn = isAuthenticated();

// Check token expiration
const tokenInfo = getTokenExpirationInfo(token);

// Refresh tokens if needed
const validTokens = await ensureValidTokens();
```

## 🎯 Demo Features

Visit `/demo` when authenticated to see:

- Current authentication status
- User profile information
- Token expiration details
- Token refresh functionality
- Real-time status updates

## 🔒 Security Features

- **PKCE Implementation**: Protects against authorization code interception
- **State Parameter**: CSRF protection for authorization requests
- **Token Validation**: Proper JWT validation and expiration checking
- **Secure Storage**: Automatic cleanup of expired tokens
- **Error Handling**: Comprehensive error handling for all scenarios

## 🧪 Testing Scenarios

1. **Normal Login**: Complete authentication flow
2. **Token Expiration**: Automatic refresh handling
3. **Logout**: Proper session termination
4. **Error Handling**: Invalid codes, expired tokens, etc.

## 📝 API Endpoints Used

- **Authorization**: `GET /oauth/v2/authorize`
- **Token Exchange**: `POST /oauth/v2/token`
- **User Info**: `GET /oidc/v1/userinfo`
- **Logout**: `GET /oidc/v1/end_session`

## 🚀 Production Considerations

- Configure HTTPS for production
- Use secure session storage
- Implement proper error logging
- Add rate limiting for auth endpoints
- Consider using HTTP-only cookies for tokens

## 📚 References

- [OAuth 2.0 RFC 6749](https://tools.ietf.org/html/rfc6749)
- [PKCE RFC 7636](https://tools.ietf.org/html/rfc7636)
- [OpenID Connect Core 1.0](https://openid.net/specs/openid-connect-core-1_0.html)
- [Zitadel Documentation](https://zitadel.com/docs)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License.
