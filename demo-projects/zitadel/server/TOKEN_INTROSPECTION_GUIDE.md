# Token Introspection with Zitadel - Complete Guide

## Current Issue Analysis

You received an `unauthorized_client` error when trying to use a Service User key file for token introspection. This is the **correct behavior** according to Zitadel's architecture.

## Key Concepts (From Zitadel Documentation)

### 1. Service Users vs API Applications

**Service Users:**
- Purpose: Obtain access tokens for accessing protected resources
- Authentication: Use JWT Profile with service user key
- Cannot: Validate tokens via introspection endpoint
- Use case: Backend services that need to call APIs

**API Applications:**
- Purpose: Validate tokens received from clients
- Authentication: Use JWT Profile with API application key
- Can: Call introspection endpoint to validate tokens
- Use case: Resource servers that need to validate incoming tokens

### 2. The Problem with Your Current Code

Your code is using a **Service User key** to authenticate with the introspection endpoint, but Zitadel requires an **API Application key** for this purpose.

```typescript
// ❌ WRONG: Using Service User key for introspection
const jwtAssertion = generateJWTAssertion(); // Service User JWT
// This fails with "unauthorized_client"
```

## Correct Implementation Approach

### Option 1: Remove Token Validation (Current Fix)

Since you're using Service User authentication, you cannot validate tokens via introspection. This is the approach implemented in the current fix.

**When to use this:**
- You're building a client application that only needs to generate tokens
- Token validation is handled by the resource server (API) you're calling
- You don't need to validate tokens in your application

### Option 2: Implement Proper Token Validation

To properly validate tokens, you need to create an API Application:

#### Step 1: Create API Application in Zitadel Console
1. Go to your Zitadel project
2. Click "New" → "Application" 
3. Select "API" as application type
4. Choose "JWT" as authentication method
5. Download the API application key file

#### Step 2: Use API Application Key for Introspection
```typescript
// API Application JWT Assertion (different from Service User)
const apiJwtAssertion = generateAPIJWTAssertion();

// Introspection request
const requestData = new URLSearchParams({
    client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer',
    client_assertion: apiJwtAssertion, // API Application JWT
    token: tokenToValidate
});
```

#### Step 3: API Application JWT Format
```typescript
// API Application JWT payload
const payload = {
    iss: apiApplicationKey.clientId,    // API Application Client ID
    sub: apiApplicationKey.clientId,    // API Application Client ID  
    aud: ZITADEL_DOMAIN,               // Zitadel domain
    exp: now + 3600,                   // Expires in 1 hour
    iat: now                           // Issued at
};
```

### Option 3: Mixed Approach (Recommended for APIs)

If you're building an API that needs both capabilities:

1. **Use Service User** for calling other APIs (token generation)
2. **Use API Application** for validating incoming tokens (introspection)

```typescript
// Two different key files
const serviceUserKey = loadServiceUserKey('./keys/service-user.json');
const apiApplicationKey = loadAPIApplicationKey('./keys/api-application.json');

// Generate tokens for outgoing API calls
const clientToken = generateTokenWithServiceUser(serviceUserKey);

// Validate tokens from incoming requests  
const validationResult = validateTokenWithAPIApplication(apiApplicationKey, incomingToken);
```

## Why This Architecture?

This separation ensures:
- **Service Users** can only obtain tokens (principle of least privilege)
- **API Applications** can validate tokens but aren't meant to access resources
- Clear separation of concerns between token generation and validation
- Better security model

## Your Current Server

Your current server is now correctly configured as a **Service User token generator**:

✅ **What it does:**
- Generates access tokens using Service User authentication
- Includes custom claims (site_id) in token requests
- Provides service information endpoint

❌ **What it cannot do:**
- Validate tokens via introspection (requires API Application)
- Act as a resource server for token validation

## Next Steps

Choose your approach:

1. **Keep current setup**: Use this server only for token generation
2. **Add API Application**: Create separate API Application for token validation
3. **Separate services**: Split into two services (token generator + validator)

## Reference Links

- [Zitadel Token Introspection Guide](https://zitadel.com/docs/guides/integrate/token-introspection/private-key-jwt)
- [Service Users Documentation](https://zitadel.com/docs/guides/integrate/service-users)
- [API Applications Documentation](https://zitadel.com/docs/guides/integrate/token-introspection)
- [Example Repository](https://github.com/zitadel/examples-api-access-and-token-introspection)
