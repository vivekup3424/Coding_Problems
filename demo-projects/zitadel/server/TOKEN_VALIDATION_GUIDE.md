# Token Validation with Zitadel Service User

This document explains how the server validates tokens using Zitadel's service user for token introspection.

## Overview

The server has been updated to properly validate tokens using Zitadel's service user through the token introspection endpoint. This is the recommended approach for server-side token validation as it:

1. Checks if the token is still active (not revoked)
2. Validates token scope and audience
3. Provides real-time validation against Zitadel's authorization server

## Authentication Methods

### 1. JWT-Based Authentication (Primary Method)
- Uses `private_key_jwt` authentication method
- Generates a JWT signed with the service user's private key
- More efficient as it doesn't require a separate token request
- Used in `introspectTokenWithJWT()` function

### 2. Bearer Token Authentication (Fallback)
- First obtains a service user access token using JWT assertion
- Uses the access token for subsequent introspection requests
- Includes token caching to reduce API calls
- Used in `introspectToken()` function

## Key Features

### Service User Setup
- Loads service user credentials from `./keys/su.json`
- Validates required fields: `keyId`, `key`, `userId`
- Proper error handling and startup validation

### Token Caching
- Caches service user tokens to reduce API calls
- 5-minute buffer before token expiry
- Automatic token refresh when needed

### Comprehensive Validation
- Validates token using Zitadel's introspection endpoint
- Checks token expiration (`exp` claim)
- Checks token validity time (`nbf` claim)
- Prioritizes introspection results over JWT decode for reliability

### Error Handling
- Detailed error logging for debugging
- Graceful fallback handling
- Proper HTTP status codes and error messages

## API Endpoints

### Authentication Endpoints
- `POST /zitadel-poc/auth/store-tokens` - Store authentication tokens in session
- `POST /zitadel-poc/auth/introspect` - Test token introspection (debug endpoint)
- `POST /zitadel-poc/auth/logout` - Logout and clear session

### Protected Endpoints
All protected endpoints use the `validateToken` middleware which:
1. Extracts token from Authorization header or session
2. Validates token using service user introspection
3. Attaches user information to request object

## Testing Token Introspection

### Test Endpoint
```bash
POST /zitadel-poc/auth/introspect
Content-Type: application/json

{
  "token": "your_access_token_here",
  "method": "jwt"  // or "bearer"
}
```

### Response
```json
{
  "introspection": {
    "active": true,
    "sub": "user_id",
    "email": "user@example.com",
    "exp": 1234567890,
    "client_id": "your_client_id",
    // ... other token claims
  },
  "method": "jwt",
  "message": "Token introspection completed"
}
```

## Configuration

### Environment Variables
- `ZITADEL_DOMAIN` - Your Zitadel domain (required)
- `CLIENT_ID` - Your application's client ID (required)
- `PORT` - Server port (default: 8080)
- `NODE_ENV` - Environment (affects CORS and session settings)

### Service User Credentials
File: `./keys/su.json`
```json
{
  "type": "serviceaccount",
  "keyId": "your_key_id",
  "key": "-----BEGIN RSA PRIVATE KEY-----\n...\n-----END RSA PRIVATE KEY-----",
  "userId": "your_service_user_id"
}
```

## Security Considerations

1. **Service User Permissions**: Ensure service user has proper permissions for token introspection
2. **Key Security**: Protect service user private keys
3. **Token Caching**: Cached tokens are stored in memory and cleared on server restart
4. **Error Handling**: Sensitive information is not exposed in error messages

## Troubleshooting

### Common Issues

1. **Service User Authentication Failed**
   - Check service user credentials format
   - Verify key permissions in Zitadel
   - Check Zitadel domain configuration

2. **Token Introspection Failed**
   - Verify token format and validity
   - Check service user has introspection permissions
   - Review network connectivity to Zitadel

3. **Invalid Token Format**
   - Ensure token is properly extracted from Authorization header
   - Check for Bearer prefix in header

### Debug Logging
The server includes comprehensive logging for:
- Service user token acquisition
- Token introspection requests/responses
- Validation errors and failures

## Best Practices

1. Use JWT-based authentication for better performance
2. Cache service user tokens appropriately
3. Always validate tokens server-side for security
4. Handle token expiration gracefully
5. Use proper error handling and logging
6. Regularly rotate service user keys

This implementation follows Zitadel's recommended practices for server-side token validation and provides a robust foundation for secure API authentication.
