# Dual Service User Configuration

This server now supports two separate service users for different purposes:

## Service Users

### 1. Introspection Service User (`./keys/api.json`)
- **Purpose**: Token introspection using OAuth2 introspection endpoint
- **Type**: API grants key
- **Usage**: Validates tokens from client applications
- **File**: `./keys/api.json`
- **Fields**: `keyId`, `key`, `clientId`, `appId`

### 2. Service User (`./keys/su.json`)
- **Purpose**: Access ZITADEL APIs for management operations
- **Type**: Service account
- **Usage**: Generate tokens for accessing ZITADEL Management API
- **File**: `./keys/su.json`
- **Fields**: `keyId`, `key`, `userId`, `expirationDate`

## Key Differences

| Feature | Introspection Service | Service User |
|---------|---------------------|-------------|
| **File** | `./keys/api.json` | `./keys/su.json` |
| **Type** | API grants | Service account |
| **Client ID** | `clientId` field | `userId` field |
| **Purpose** | Token introspection | ZITADEL API access |
| **Scope** | Token validation | `urn:zitadel:iam:org:project:id:zitadel:aud` |

## Endpoints

### Token Generation
- **POST** `/api/generate-token`
- Uses service user credentials from `./keys/su.json`
- Includes ZITADEL API audience scope
- Returns access token with custom claims

### Token Validation
- **POST** `/api/validate-token`
- Uses introspection service credentials from `./keys/api.json`
- Validates tokens via OAuth2 introspection endpoint

### ZITADEL API Access
- **GET** `/api/zitadel/org/me`
- Demonstrates accessing ZITADEL Management API
- Uses service user credentials to get organization data

### Service Information
- **GET** `/api/service-info`
- Shows configuration for both service users
- Returns credentials info and endpoints

## Configuration

### Environment Variables
```
ZITADEL_DOMAIN=https://auth.keus.in
PROJECT_ID=325033691317272582
```

### Service User Scopes
For ZITADEL API access, the service user token includes:
- `openid profile` - Basic OpenID Connect scopes
- `urn:zitadel:iam:org:project:id:zitadel:aud` - ZITADEL API audience (required)
- `urn:zitadel:iam:org:project:id:${PROJECT_ID}:aud` - Project-specific audience

## Security Notes

1. **Separation of Concerns**: Different service users for different purposes
2. **Minimal Permissions**: Each service user has only the permissions it needs
3. **Token Expiration**: Service user tokens expire in 5 minutes (300 seconds)
4. **JWT Assertion**: Uses RS256 signing with private keys
5. **Audience Validation**: Tokens include proper audience claims

## Documentation References

- [ZITADEL API Access Guide](https://zitadel.com/docs/guides/integrate/zitadel-apis/access-zitadel-apis)
- [Service User Authentication](https://zitadel.com/docs/guides/integrate/service-users/authenticate-service-users)
- [Token Introspection](https://zitadel.com/docs/guides/integrate/token-introspection/private-key-jwt)
