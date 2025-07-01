# CASL Authorization Service

A comprehensive authorization service for home automation systems built with MoleculerJS and CASL (Code Access Security Layer).

## Features

- **Authentication Service**: User login and JWT token management
- **Local Authorization Service**: Permission checking for local home network operations  
- **Cloud Authorization Service**: Permission checking for cloud-based operations
- **Dynamic User Permissions**: Customizable permissions per user rather than static roles
- **Time-based Access Control**: Restrict access based on time of day
- **Device & Room-level Permissions**: Granular control over smart home devices and rooms

## Architecture

### Services

1. **Authentication Service** (`authentication.service.ts`)
   - User login/logout
   - JWT token generation and validation
   - Password verification

2. **Local Authorization Service** (`local-authorization.service.ts`)
   - Checks permissions using `local-permissions.json`
   - Handles local smart home device control
   - Time-based access restrictions

3. **Cloud Authorization Service** (`cloud-authorization.service.ts`) 
   - Checks permissions using `cloud-permissions.json`
   - Handles cloud-based operations
   - User and home management permissions

### Data Structure

- `authentication-data.json` - User profiles and authentication data
- `local-permissions.json` - Local device control permissions
- `cloud-permissions.json` - Cloud operation permissions  
- `devices-data.json` - Smart home device definitions
- `rooms-data.json` - Room and scene definitions

## Getting Started

### Prerequisites

- Node.js >= 16.0.0
- npm or yarn

### Installation

```bash
npm install
```

### Development

```bash
npm run dev
```

### Build

```bash
npm run build
npm start
```

### Testing

```bash
npm test
npm run test:watch
```

## Usage

### Starting the Services

```bash
npm run dev
```

This will start all three MoleculerJS services:
- `authentication` 
- `local-authorization`
- `cloud-authorization`

### Example Permission Check

```typescript
// Check if user can control a specific device
const canControl = await broker.call('local-authorization.can', {
  userId: 'user_002',
  action: 'control', 
  subject: 'device',
  resource: { 
    id: 'device_001', 
    type: 'smart_light',
    homeId: 'home_001' 
  }
});
```

## Configuration

Environment variables:
- `JWT_SECRET` - JWT signing secret
- `JWT_EXPIRES_IN` - Token expiration time
- `TRANSPORTER` - MoleculerJS transporter
- `CACHER` - MoleculerJS cacher

## License

MIT
