const { Service } = require("moleculer");
const ApiGateway = require("moleculer-web");
const { MoleculerError } = require("moleculer").Errors;
const authUtils = require("../utils/auth");

class ApiService extends Service {
  constructor(broker) {
    super(broker);

    this.parseServiceSchema({
      name: "api",
      mixins: [ApiGateway],

      settings: {
        port: process.env.PORT || 3000,
        ip: "0.0.0.0",

        use: [],

        routes: [
          {
            path: "/api",
            
            whitelist: [
              // Authentication routes
              "v1.cloud-auth.*",
              // Authorization routes  
              "v1.cloud-authorization.*",
              "v1.local-authorization.*"
            ],

            use: [],

            mergeParams: true,

            authentication: false,

            authorization: false,

            autoAliases: true,

            aliases: {
              // Authentication endpoints
              "POST /auth/register": "v1.cloud-auth.register",
              "POST /auth/login": "v1.cloud-auth.login",
              "POST /auth/verify": "v1.cloud-auth.verify",
              "POST /auth/refresh": "v1.cloud-auth.refreshToken",
              "POST /auth/change-password": "v1.cloud-auth.changePassword",
              "GET /auth/profile": "v1.cloud-auth.getProfile",

              // Cloud Authorization endpoints
              "POST /authz/authorize": "v1.cloud-authorization.authorize",
              "POST /authz/permissions": "v1.cloud-authorization.createPermission",
              "POST /authz/roles": "v1.cloud-authorization.createRole",
              "POST /authz/roles/assign-permissions": "v1.cloud-authorization.assignPermissionsToRole",
              "POST /authz/users/assign-roles": "v1.cloud-authorization.assignRolesToUser",
              "GET /authz/permissions": "v1.cloud-authorization.listPermissions",
              "GET /authz/roles": "v1.cloud-authorization.listRoles",
              "GET /authz/users/:userId/permissions": "v1.cloud-authorization.getUserPermissions",

              // Local Authorization endpoints
              "POST /local-authz/authorize": "v1.local-authorization.authorize",
              "POST /local-authz/sync/:userId": "v1.local-authorization.syncPermissions",
              "POST /local-authz/offline-mode": "v1.local-authorization.setOfflineMode",
              "POST /local-authz/emergency": "v1.local-authorization.emergencyAuthorize",
              "GET /local-authz/status": "v1.local-authorization.getStatus"
            },

            callingOptions: {},

            bodyParsers: {
              json: {
                strict: false,
                limit: "1MB"
              },
              urlencoded: {
                extended: true,
                limit: "1MB"
              }
            },

            mappingPolicy: "all",

            logging: true
          },

          // Protected routes that require authentication
          {
            path: "/api/protected",
            
            whitelist: [
              "v1.cloud-auth.*",
              "v1.cloud-authorization.*"
            ],

            use: [],

            mergeParams: true,

            authentication: true,

            authorization: false,

            autoAliases: true,

            aliases: {
              "GET /profile": "v1.cloud-auth.getProfile",
              "POST /change-password": "v1.cloud-auth.changePassword",
              "GET /permissions": "v1.cloud-authorization.getUserPermissions"
            },

            callingOptions: {},

            bodyParsers: {
              json: {
                strict: false,
                limit: "1MB"
              }
            },

            mappingPolicy: "all",

            logging: true,

            // Authentication middleware
            onBeforeCall: this.authenticateRoute.bind(this)
          },

          // Health check and documentation
          {
            path: "/",
            
            use: [],

            mergeParams: true,

            authentication: false,

            authorization: false,

            autoAliases: false,

            aliases: {
              "GET /": "api.welcome",
              "GET /health": "api.health",
              "GET /docs": "api.docs"
            },

            callingOptions: {},

            mappingPolicy: "all",

            logging: true
          }
        ],

        // Global CORS settings for all routes
        cors: {
          origin: ["*"],
          methods: ["GET", "OPTIONS", "POST", "PUT", "DELETE"],
          allowedHeaders: ["Content-Type", "Authorization"],
          exposedHeaders: [],
          credentials: false,
          maxAge: 3600
        },

        // Global error handler
        onError: this.handleError.bind(this)
      },

      actions: {
        welcome: {
          rest: "GET /",
          handler: this.welcome
        },
        health: {
          rest: "GET /health",
          handler: this.health
        },
        docs: {
          rest: "GET /docs",
          handler: this.docs
        }
      },

      methods: {
        authenticate: this.authenticate,
        authenticateRoute: this.authenticateRoute,
        handleError: this.handleError
      },

      started: this.serviceStarted
    });
  }

  async serviceStarted() {
    this.logger.info(`🌐 API Gateway started on http://localhost:${this.settings.port}`);
    this.logger.info("📚 API Documentation available at http://localhost:3000/docs");
    this.logger.info("❤️ Health check available at http://localhost:3000/health");
  }

  /**
   * Welcome endpoint
   */
  async welcome(ctx) {
    return {
      message: "🏠 Home Automation Authentication & Authorization Platform",
      version: "1.0.0",
      timestamp: new Date().toISOString(),
      services: {
        authentication: "Cloud Authentication Service",
        cloudAuthorization: "Cloud Authorization Service", 
        localAuthorization: "Local Authorization Service"
      },
      endpoints: {
        auth: "/api/auth/*",
        authorization: "/api/authz/*",
        localAuthorization: "/api/local-authz/*",
        protected: "/api/protected/*",
        health: "/health",
        docs: "/docs"
      }
    };
  }

  /**
   * Health check endpoint
   */
  async health(ctx) {
    try {
      // Check service health
      const services = await this.broker.call("$node.health");
      
      // Check database connectivity
      let dbStatus = "unknown";
      try {
        await this.broker.call("v1.cloud-auth.getProfile", {}, { 
          meta: { user: { userId: "health-check" } },
          timeout: 3000 
        });
        dbStatus = "disconnected"; // Expected to fail for health check user
      } catch (error) {
        dbStatus = error.type === "USER_NOT_FOUND" ? "connected" : "disconnected";
      }

      // Check local authorization status
      let localAuthStatus = "unknown";
      try {
        const localStatus = await this.broker.call("v1.local-authorization.getStatus", {}, { timeout: 3000 });
        localAuthStatus = localStatus.success ? "healthy" : "unhealthy";
      } catch (error) {
        localAuthStatus = "unavailable";
      }

      return {
        status: "healthy",
        timestamp: new Date().toISOString(),
        uptime: process.uptime(),
        services: {
          broker: services ? "healthy" : "unhealthy",
          database: dbStatus,
          localAuthorization: localAuthStatus
        },
        memory: process.memoryUsage(),
        version: "1.0.0"
      };

    } catch (error) {
      this.logger.error("Health check error:", error);
      
      return {
        status: "unhealthy",
        timestamp: new Date().toISOString(),
        error: error.message
      };
    }
  }

  /**
   * API documentation endpoint
   */
  async docs(ctx) {
    return {
      title: "Home Automation Auth Platform API",
      version: "1.0.0",
      description: "Authentication and Authorization API for Home Automation Systems",
      baseUrl: `http://localhost:${this.settings.port}/api`,
      endpoints: {
        authentication: {
          "POST /auth/register": "Register new user",
          "POST /auth/login": "Login user",
          "POST /auth/verify": "Verify JWT token",
          "POST /auth/refresh": "Refresh JWT token",
          "GET /auth/profile": "Get user profile (requires auth)",
          "POST /auth/change-password": "Change password (requires auth)"
        },
        cloudAuthorization: {
          "POST /authz/authorize": "Check authorization",
          "POST /authz/permissions": "Create permission",
          "POST /authz/roles": "Create role",
          "GET /authz/permissions": "List all permissions",
          "GET /authz/roles": "List all roles",
          "POST /authz/roles/assign-permissions": "Assign permissions to role",
          "POST /authz/users/assign-roles": "Assign roles to user",
          "GET /authz/users/:userId/permissions": "Get user permissions"
        },
        localAuthorization: {
          "POST /local-authz/authorize": "Local authorization check",
          "POST /local-authz/sync/:userId": "Sync user permissions for offline use",
          "POST /local-authz/offline-mode": "Enable/disable offline mode",
          "POST /local-authz/emergency": "Emergency authorization",
          "GET /local-authz/status": "Get local authorization status",
          "DELETE /local-authz/cache": "Clear local cache"
        }
      },
      authentication: {
        type: "Bearer Token",
        description: "Include 'Authorization: Bearer <token>' header for protected endpoints"
      },
      examples: {
        register: {
          url: "POST /api/auth/register",
          body: {
            email: "user@example.com",
            username: "username",
            password: "password123",
            firstName: "John",
            lastName: "Doe"
          }
        },
        login: {
          url: "POST /api/auth/login", 
          body: {
            email: "user@example.com",
            password: "password123"
          }
        },
        authorize: {
          url: "POST /api/authz/authorize",
          body: {
            userId: "user-id",
            resource: "device",
            action: "read"
          }
        }
      }
    };
  }

  /**
   * Authentication middleware for protected routes
   */
  async authenticateRoute(ctx, route, req, res) {
    const authHeader = req.headers.authorization;
    const token = authUtils.extractTokenFromHeader(authHeader);
    
    if (!token) {
      throw new MoleculerError("Authentication required", 401, "AUTH_REQUIRED", {
        headers: { "WWW-Authenticate": "Bearer" }
      });
    }

    try {
      const decoded = authUtils.verifyToken(token);
      ctx.meta.user = decoded;
      ctx.meta.token = token;
    } catch (error) {
      throw new MoleculerError("Invalid or expired token", 401, "INVALID_TOKEN", {
        headers: { "WWW-Authenticate": "Bearer" }
      });
    }
  }

  /**
   * Authenticate user from JWT token
   */
  async authenticate(ctx, route, req) {
    const authHeader = req.headers.authorization;
    const token = authUtils.extractTokenFromHeader(authHeader);
    
    if (!token) {
      throw new MoleculerError("Authentication required", 401, "AUTH_REQUIRED");
    }

    try {
      const decoded = authUtils.verifyToken(token);
      return decoded;
    } catch (error) {
      throw new MoleculerError("Invalid token", 401, "INVALID_TOKEN");
    }
  }

  /**
   * Global error handler
   */
  handleError(req, res, err) {
    this.logger.error("API Error:", err);
    
    // Set error response
    res.setHeader("Content-Type", "application/json; charset=utf-8");
    
    let statusCode = 500;
    let errorResponse = {
      success: false,
      error: "Internal Server Error",
      message: err.message || "An unexpected error occurred"
    };

    if (err instanceof MoleculerError) {
      statusCode = err.code || 500;
      errorResponse.error = err.type || err.name;
      errorResponse.code = err.type;
      
      if (err.data) {
        errorResponse.data = err.data;
      }
    }

    res.writeHead(statusCode);
    res.end(JSON.stringify(errorResponse));
  }
}

module.exports = ApiService;
