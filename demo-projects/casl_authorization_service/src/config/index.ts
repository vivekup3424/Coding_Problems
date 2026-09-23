export const config = {
  // JWT Configuration
  jwt: {
    secret: process.env.JWT_SECRET || 'your-super-secret-jwt-key-change-in-production',
    expiresIn: process.env.JWT_EXPIRES_IN || '24h',
    issuer: 'casl-auth-service',
    audience: 'home-automation-system'
  } as const,

  // Service Configuration
  services: {
    authentication: {
      name: 'authentication',
      version: "1.0.0"
    },
    localAuthorization: {
      name: 'local-authorization', 
      version: "1.0.0"
    },
    cloudAuthorization: {
      name: 'cloud-authorization',
      version: "1.0.0"
    }
  },

  // Data file paths
  dataFiles: {
    users: './authentication-data.json',
    localPermissions: './data/local-permissions.json',
    cloudPermissions: './data/cloud-permissions.json',
    devices: './data/devices-data.json',
    rooms: './data/rooms-data.json'
  },

  // Security
  security: {
    bcryptRounds: 10,
    maxLoginAttempts: 5,
    lockoutDuration: 15 * 60 * 1000, // 15 minutes
    sessionTimeout: 24 * 60 * 60 * 1000 // 24 hours
  },

  // Default roles
  roles: {
    SUPER_ADMIN: 'super_admin',
    HOME_ADMIN: 'home_admin',
    EMERGENCY_OVERRIDE: 'emergency_override'
  }
};

export default config;
