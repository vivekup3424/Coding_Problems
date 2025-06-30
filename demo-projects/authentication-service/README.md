# Home Automation Authentication & Authorization Platform

A comprehensive microservices-based authentication and authorization platform built with MoleculerJS for home automation systems. This platform provides both cloud-based and local authorization capabilities with offline support.

## Features

### 🔐 Cloud Authentication Service
- User registration and login
- JWT token-based authentication
- Password management
- User profile management
- Secure password hashing with bcrypt

### ☁️ Cloud Authorization Service
- Role-based access control (RBAC)
- Dynamic permission management
- Resource and action-based permissions
- System roles (admin, homeowner, user)
- Permission assignment to roles
- Role assignment to users

### 🏠 Local Authorization Service
- Local authorization with cloud fallback
- Offline mode support
- Permission caching for offline use
- Emergency authorization for critical actions
- Local-only permissions for emergency scenarios
- Automatic cloud sync when connectivity is restored

### 🌐 API Gateway
- RESTful API endpoints
- JWT authentication middleware
- CORS support
- Comprehensive error handling
- API documentation
- Health check endpoints

## Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   API Gateway   │    │  Cloud Auth     │    │ Cloud AuthZ     │
│                 │    │  Service        │    │ Service         │
│ ┌─────────────┐ │    │                 │    │                 │
│ │   HTTP      │ │    │ • Registration  │    │ • RBAC          │
│ │   Endpoints │ │◄──►│ • Login         │◄──►│ • Permissions   │
│ │             │ │    │ • JWT Tokens    │    │ • Roles         │
│ └─────────────┘ │    │ • User Profile  │    │ • Authorization │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                        │                        │
         │                        │                        │
         ▼                        ▼                        ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│ Local AuthZ     │    │    MongoDB      │    │     Redis       │
│ Service         │    │                 │    │                 │
│                 │    │ • Users         │    │ • Caching       │
│ • Offline Mode  │    │ • Roles         │    │ • Transport     │
│ • Emergency     │    │ • Permissions   │    │ • Sessions      │
│ • Local Cache   │    │                 │    │                 │
│ • Cloud Sync    │    │                 │    │                 │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## Quick Start

### Prerequisites
- Node.js 16+ 
- MongoDB
- Redis
- npm or yarn

### Installation

1. **Clone and install dependencies:**
```bash
git clone <repository-url>
cd authentication-service
npm install
```

2. **Setup environment:**
```bash
cp .env.example .env
# Edit .env with your configuration
```

3. **Start required services:**
```bash
# Start MongoDB
mongod

# Start Redis  
redis-server
```

4. **Run the application:**
```bash
# Development mode with hot reload
npm run dev

# Production mode
npm start
```

The API will be available at `http://localhost:3000`

## API Documentation

Visit `http://localhost:3000/docs` for interactive API documentation.

### Authentication Endpoints

#### Register User
```bash
POST /api/auth/register
Content-Type: application/json

{
  "email": "user@example.com",
  "username": "johndoe", 
  "password": "securepassword123",
  "firstName": "John",
  "lastName": "Doe"
}
```

#### Login
```bash
POST /api/auth/login
Content-Type: application/json

{
  "email": "user@example.com",
  "password": "securepassword123"
}
```

#### Verify Token
```bash
POST /api/auth/verify
Content-Type: application/json

{
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

### Authorization Endpoints

#### Check Authorization
```bash
POST /api/authz/authorize
Content-Type: application/json

{
  "userId": "user-id-here",
  "resource": "device",
  "action": "read"
}
```

#### Create Permission
```bash
POST /api/authz/permissions
Content-Type: application/json

{
  "name": "device:control",
  "resource": "device",
  "action": "control",
  "description": "Control device states"
}
```

### Local Authorization Endpoints

#### Local Authorization Check
```bash
POST /api/local-authz/authorize
Content-Type: application/json

{
  "userId": "user-id-here",
  "resource": "device", 
  "action": "emergency-stop"
}
```

#### Emergency Authorization
```bash
POST /api/local-authz/emergency
Content-Type: application/json

{
  "userId": "user-id-here",
  "action": "emergency-stop",
  "authCode": "HOME911"
}
```

## Permission System

### Permission Format
Permissions follow the pattern: `resource:action`

Examples:
- `device:read` - Read device information
- `device:write` - Control devices
- `device:*` - All device permissions
- `*:*` - All permissions

### Default System Roles

| Role | Description | Default Permissions |
|------|-------------|-------------------|
| `admin` | Full system administrator | `*:*` (all permissions) |
| `homeowner` | Home owner with device management | `device:*`, `room:*`, `automation:*` |
| `user` | Standard user | `device:read`, `room:read` |

### Default System Permissions

#### Device Permissions
- `device:read` - View device information
- `device:write` - Control devices
- `device:admin` - Manage device settings
- `device:emergency-stop` - Emergency device shutdown

#### Room Permissions  
- `room:read` - View room information
- `room:write` - Modify room settings
- `room:admin` - Manage room configuration

#### Automation Permissions
- `automation:read` - View automations
- `automation:write` - Create/edit automations
- `automation:execute` - Run automations

#### System Permissions
- `system:read` - View system status
- `system:admin` - System administration

## Local Authorization & Offline Mode

The local authorization service provides robust offline capabilities:

### Features
- **Automatic Fallback**: Switches to offline mode when cloud connectivity is lost
- **Permission Caching**: Caches user permissions locally for offline use
- **Emergency Actions**: Always-available emergency authorizations
- **Auto-Sync**: Automatically syncs with cloud when connectivity returns

### Emergency Permissions
These permissions are always available locally:
- `device:emergency-stop`
- `security:alarm-disable` 
- `lighting:emergency`

### Usage
```bash
# Check local authorization status
GET /api/local-authz/status

# Enable offline mode manually
POST /api/local-authz/offline-mode
{
  "enabled": true
}

# Emergency authorization
POST /api/local-authz/emergency
{
  "userId": "user-id",
  "action": "emergency-stop",
  "authCode": "HOME911"
}
```

## Development

### Project Structure
```
authentication-service/
├── services/                 # MoleculerJS services
│   ├── api.service.js       # API Gateway
│   ├── cloud-auth.service.js # Authentication  
│   ├── cloud-authorization.service.js # Cloud Authorization
│   └── local-authorization.service.js # Local Authorization
├── models/                   # Data models and validation
│   ├── user.js              # User model schemas
│   └── permission.js        # Permission/role schemas
├── utils/                    # Utility functions
│   ├── auth.js              # Authentication utilities
│   └── database.js          # Database connection
├── moleculer.config.js       # MoleculerJS configuration
├── index.js                 # Application entry point
└── package.json             # Dependencies and scripts
```

### Available Scripts

```bash
# Development with hot reload
npm run dev

# Production start
npm start

# Run tests
npm test

# Lint code
npm run lint
```

### Environment Variables

| Variable | Description | Default |
|----------|-------------|---------|
| `NODE_ENV` | Environment mode | `development` |
| `PORT` | Server port | `3000` |
| `MONGODB_URI` | MongoDB connection string | `mongodb://localhost:27017` |
| `DB_NAME` | Database name | `home_automation_auth` |
| `REDIS_HOST` | Redis host | `localhost` |
| `REDIS_PORT` | Redis port | `6379` |
| `JWT_SECRET` | JWT signing secret | Required in production |
| `JWT_EXPIRES_IN` | JWT expiration time | `24h` |
| `EMERGENCY_AUTH_CODE` | Emergency authorization code | `HOME911` |

## Security Considerations

1. **JWT Secret**: Use a strong, random JWT secret in production
2. **Password Hashing**: Uses bcrypt with 12 salt rounds
3. **Emergency Codes**: Change default emergency authorization codes
4. **HTTPS**: Use HTTPS in production environments
5. **Database Security**: Secure MongoDB with authentication
6. **Redis Security**: Secure Redis instance with password
7. **Rate Limiting**: Consider implementing rate limiting for production

## Monitoring & Health Checks

### Health Check Endpoint
```bash
GET /health
```

Returns system health information including:
- Service broker status
- Database connectivity
- Local authorization status
- Memory usage
- Uptime information

### Logging
The application uses structured logging with different levels:
- `error`: Error conditions
- `warn`: Warning conditions  
- `info`: Informational messages
- `debug`: Debug information

## Production Deployment

### Docker Support
Create a `Dockerfile`:

```dockerfile
FROM node:16-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .
EXPOSE 3000
CMD ["npm", "start"]
```

### Environment Setup
1. Set strong JWT secrets
2. Configure secure database connections
3. Set up Redis clustering for high availability
4. Configure proper logging and monitoring
5. Set up HTTPS termination
6. Configure environment-specific permissions

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new features
5. Run the test suite
6. Submit a pull request

## License

This project is licensed under the ISC License.

## Support

For support and questions:
- Check the API documentation at `/docs`
- Review the health status at `/health`
- Check service logs for debugging information
