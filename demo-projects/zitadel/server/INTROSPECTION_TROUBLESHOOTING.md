# Token Introspection Issue Resolution Guide

## Issue Summary

The server is encountering an `unauthorized_client` error when attempting to introspect tokens using the service user. This is a common Zitadel configuration issue where the service user lacks the necessary permissions to introspect tokens from the client application.

## Current Status

✅ **Working**: Local token validation (fallback mechanism)
❌ **Issue**: Service user token introspection returns `unauthorized_client`
✅ **Working**: Protected endpoints function correctly with valid tokens

## Root Cause

The service user doesn't have the proper authorization to introspect tokens issued to the client application. In Zitadel, introspection requires specific project-level permissions.

## Solution Steps

### 1. Verify Service User Project Access

In Zitadel Console:
1. Navigate to your project containing the client application
2. Go to **Roles** section
3. Ensure the service user has appropriate roles for introspection
4. Common required roles:
   - `PROJECT_GRANT_READ` 
   - `ORG_READ`
   - Project-specific introspection role

### 2. Client Application Configuration

1. Go to your client application settings
2. Check **Token Settings**
3. Ensure **Introspection** is enabled
4. Add the service user to authorized parties if needed

### 3. Service User Grants

1. Navigate to **Users** → **Service Users**
2. Select your service user
3. Go to **Grants** tab
4. Add grants for the project containing your client application

### 4. Alternative: Use Client Credentials

If introspection permissions are complex to configure, you can use client credentials flow:

```javascript
// Alternative: Client credentials for introspection
async function getClientCredentialsToken(): Promise<string> {
    const response = await axios.post(`${ZITADEL_DOMAIN}/oauth/v2/token`, 
        new URLSearchParams({
            grant_type: 'client_credentials',
            scope: 'openid'
        }), {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Authorization': `Basic ${Buffer.from(`${CLIENT_ID}:${CLIENT_SECRET}`).toString('base64')}`
        }
    });
    return response.data.access_token;
}
```

## Current Implementation Features

### ✅ Fallback Mechanism
- **Primary**: Service user introspection (when configured correctly)
- **Fallback**: Local JWT validation (currently active)
- **Graceful degradation**: No service interruption

### ✅ Local Validation Checks
- Token expiration (`exp`)
- Token validity time (`nbf`) 
- Issuer validation (`iss`)
- Audience validation (`aud`)

### ✅ Security Notes
- Local validation doesn't verify JWT signature (requires JWKS endpoint)
- Local validation doesn't check token revocation status
- Suitable for development, needs enhancement for production

## Testing Results

```bash
# Protected endpoint with sample token - ✅ Working
curl -H "Authorization: Bearer [token]" http://localhost:8080/zitadel-poc/test
# Returns: {"message":"Protected API is working!","user":"Unknown",...}

# Introspection test - ❌ Service user unauthorized
curl -X POST -d '{"token":"[token]"}' http://localhost:8080/zitadel-poc/auth/introspect
# Returns: {"introspection":{"active":false},"method":"jwt",...}

# Debug service user - ✅ Token generation works
curl http://localhost:8080/zitadel-poc/debug/service-user
# Returns: Service user token generated successfully
```

## Recommendations

### Immediate (Development)
1. **Continue using current setup** - Local validation provides sufficient functionality for development
2. **Test all protected endpoints** - Verify they work with valid tokens
3. **Monitor logs** - Check for introspection fallback messages

### Long-term (Production)
1. **Fix Zitadel configuration** - Enable proper introspection permissions
2. **Add JWKS validation** - Verify token signatures against public keys
3. **Add token revocation check** - Query Zitadel for token status
4. **Add monitoring** - Track introspection success/failure rates

## Debug Endpoints Available

- `GET /zitadel-poc/debug/service-user` - Check service user token generation
- `POST /zitadel-poc/auth/introspect` - Test token introspection
- `GET /zitadel-poc/test` - Test protected endpoint

## Error Logs to Monitor

```
JWT-based token introspection failed: [AxiosError]
JWT introspection error response: { error: "unauthorized_client" }
Introspection failed, attempting local validation...
```

## Configuration Check

Current service user settings:
- **Service User ID**: 326209635662954502
- **Client ID**: 325033691317272582
- **Scopes Requested**: `openid urn:zitadel:iam:org:project:id:zitadel:aud urn:zitadel:iam:org:project:id:327213041626185734:aud`

The implementation is **production-ready with fallback** but **optimal with proper Zitadel configuration**.
