const { Service } = require("moleculer");
const { MoleculerError } = require("moleculer").Errors;
const database = require("../utils/database");

class LocalAuthorizationService extends Service {
  constructor(broker) {
    super(broker);

    this.parseServiceSchema({
      name: "local-authorization",
      version: 1,

      settings: {
        // Cache settings for local authorization
        cacheEnabled: true,
        cacheTTL: 300, // 5 minutes
        
        // Local-specific permissions that don't require cloud connectivity
        localPermissions: [
          "device:emergency-stop",
          "device:local-read",
          "automation:local-execute",
          "security:alarm-disable",
          "lighting:emergency"
        ],
        
        // Offline mode settings
        offlineMode: false,
        offlinePermissions: {
          "homeowner": ["device:*", "automation:*", "lighting:*"],
          "admin": ["*:*"],
          "user": ["device:read", "lighting:read"]
        },
        
        // Local ABAC policies (for offline operation)
        localAbacPolicies: [
          {
            id: "emergency-local-override",
            name: "Emergency Local Override",
            description: "Allow emergency actions locally regardless of other restrictions",
            resource: "*",
            action: "*",
            effect: "ALLOW",
            priority: 2000,
            condition: {
              or: [
                { action: "emergency-stop" },
                { emergencyMode: true },
                { 
                  and: [
                    { resource: "security" },
                    { action: "alarm-disable" }
                  ]
                }
              ]
            }
          },
          {
            id: "device-local-access",
            name: "Device Local Access Control",
            description: "Allow device owners to control their devices locally",
            resource: "device",
            action: "*",
            effect: "ALLOW",
            priority: 800,
            condition: {
              and: [
                { deviceOwner: { equals: "userId" } },
                { action: { in: ["read", "write", "local-read"] } }
              ]
            }
          },
          {
            id: "offline-time-restriction",
            name: "Offline Time Restriction",
            description: "Restrict non-emergency actions during late hours when offline",
            resource: "*",
            action: "*",
            effect: "DENY",
            priority: 600,
            condition: {
              and: [
                { offlineMode: true },
                { userRole: { notIn: ["admin", "homeowner"] } },
                { action: { notIn: ["read", "emergency-stop"] } },
                {
                  or: [
                    { time: { before: "06:00" } },
                    { time: { after: "22:00" } }
                  ]
                }
              ]
            }
          }
        ],
        
        // Local ABAC settings
        localAbacSettings: {
          enabled: true,
          defaultDecision: "DENY",
          combiningAlgorithm: "deny-overrides"
        }
      },

      dependencies: ["cloud-authorization"],

      actions: {
        authorize: {
          params: {
            userId: { type: "string" },
            resource: { type: "string" },
            action: { type: "string" },
            context: { type: "object", optional: true }
          },
          handler: this.authorize
        },
        syncPermissions: {
          params: {
            userId: { type: "string" }
          },
          handler: this.syncPermissions
        },
        setOfflineMode: {
          params: {
            enabled: { type: "boolean" }
          },
          handler: this.setOfflineMode
        },
        getStatus: this.getStatus,
        clearCache: this.clearCache,
        emergencyAuthorize: {
          params: {
            userId: { type: "string" },
            action: { type: "string", enum: ["emergency-stop", "alarm-disable", "emergency-lighting"] },
            authCode: { type: "string", optional: true }
          },
          handler: this.emergencyAuthorize
        },
        
        // Local ABAC Actions
        evaluateLocalAbacPolicies: {
          params: {
            userId: { type: "string" },
            resource: { type: "string" },
            action: { type: "string" },
            context: { type: "object", optional: true }
          },
          handler: this.evaluateLocalAbacPolicies
        }
      },

      methods: {
        isLocalPermission: this.isLocalPermission,
        checkLocalPermission: this.checkLocalPermission,
        checkOfflinePermission: this.checkOfflinePermission,
        cacheAuthorizationResult: this.cacheAuthorizationResult,
        cacheUserPermissions: this.cacheUserPermissions,
        getUserRolesFromCache: this.getUserRolesFromCache,
        checkCloudConnectivity: this.checkCloudConnectivity,
        validateEmergencyCode: this.validateEmergencyCode,
        
        // Local ABAC methods
        evaluateLocalAbacCondition: this.evaluateLocalAbacCondition,
        extractLocalUserAttributes: this.extractLocalUserAttributes,
        extractLocalResourceAttributes: this.extractLocalResourceAttributes,
        extractLocalEnvironmentAttributes: this.extractLocalEnvironmentAttributes,
        combineLocalDecisions: this.combineLocalDecisions
      },

      events: {
        "user.login": this.handleUserLogin,
        "user.rolesChanged": this.handleUserRolesChanged
      },

      started: this.serviceStarted
    });
  }

  async serviceStarted() {
    // Initialize local authorization cache
    this.permissionCache = new Map();
    this.userRoleCache = new Map();
    
    // Check cloud connectivity
    await this.checkCloudConnectivity();
    
    this.logger.info("🏠 Local Authorization Service started");
  }

  /**
   * Enhanced local authorization check with RBAC + ABAC support
   */
  async authorize(ctx) {
    const { userId, resource, action, context = {} } = ctx.params;
    
    try {
      // Enhanced context with local information
      const enhancedContext = {
        ...context,
        offlineMode: this.settings.offlineMode,
        emergencyMode: context.emergencyMode || false
      };

      // First, try to authorize locally for emergency/critical actions
      const isLocalPermission = this.isLocalPermission(resource, action);
      if (isLocalPermission) {
        const hasLocalPermission = await this.checkLocalPermission(userId, resource, action);
        
        // If local ABAC is enabled, evaluate local policies
        let abacResult = { decision: true, policies: [] };
        if (this.settings.localAbacSettings.enabled) {
          abacResult = await this.evaluateLocalAbacPolicies({ params: { userId, resource, action, context: enhancedContext } });
        }
        
        const finalDecision = this.combineLocalDecisions(hasLocalPermission, abacResult.decision, enhancedContext);
        
        this.logger.info(`🏠 Local authorization for ${userId}: ${resource}:${action} = ${finalDecision}`);
        
        return {
          success: true,
          authorized: finalDecision,
          source: "local",
          userId,
          resource,
          action,
          context: enhancedContext,
          evaluationDetails: {
            rbac: hasLocalPermission,
            abac: abacResult,
            final: finalDecision
          }
        };
      }

      // Try cloud authorization first
      if (!this.settings.offlineMode) {
        try {
          const cloudResult = await ctx.call("v1.cloud-authorization.authorize", {
            userId,
            resource,
            action,
            context: enhancedContext
          });

          // Cache the result for future offline use
          if (cloudResult.success) {
            this.cacheAuthorizationResult(userId, resource, action, cloudResult.authorized);
          }

          return {
            ...cloudResult,
            source: "cloud"
          };

        } catch (error) {
          this.logger.warn("Cloud authorization failed, falling back to local cache:", error.message);
          this.settings.offlineMode = true;
          enhancedContext.offlineMode = true;
        }
      }

      // Fallback to cached/offline authorization with ABAC
      const hasOfflinePermission = await this.checkOfflinePermission(userId, resource, action);
      
      // Evaluate local ABAC policies for offline operation
      let offlineAbacResult = { decision: true, policies: [] };
      if (this.settings.localAbacSettings.enabled) {
        offlineAbacResult = await this.evaluateLocalAbacPolicies({ params: { userId, resource, action, context: enhancedContext } });
      }
      
      const finalDecision = this.combineLocalDecisions(hasOfflinePermission, offlineAbacResult.decision, enhancedContext);
      
      this.logger.info(`🔌 Offline authorization for ${userId}: ${resource}:${action} = ${finalDecision}`);
      
      return {
        success: true,
        authorized: finalDecision,
        source: "offline",
        userId,
        resource,
        action,
        context: enhancedContext,
        warning: "Operating in offline mode",
        evaluationDetails: {
          rbac: hasOfflinePermission,
          abac: offlineAbacResult,
          final: finalDecision
        }
      };

    } catch (error) {
      this.logger.error("Local authorization error:", error);
      return {
        success: false,
        authorized: false,
        error: error.message,
        source: "error"
      };
    }
  }

  /**
   * Sync permissions from cloud for offline use
   */
  async syncPermissions(ctx) {
    const { userId } = ctx.params;
    
    try {
      // Get user permissions from cloud
      const cloudPermissions = await ctx.call("v1.cloud-authorization.getUserPermissions", {
        userId
      });

      if (cloudPermissions.success) {
        // Cache permissions locally
        this.cacheUserPermissions(userId, cloudPermissions.permissions);
        
        this.logger.info(`📥 Synced permissions for user ${userId}`);
        
        return {
          success: true,
          message: "Permissions synced successfully",
          permissionCount: cloudPermissions.permissions.length
        };
      }

      throw new Error("Failed to get permissions from cloud");

    } catch (error) {
      this.logger.error("Sync permissions error:", error);
      throw new MoleculerError("Failed to sync permissions", 500, "SYNC_FAILED");
    }
  }

  /**
   * Set offline mode
   */
  async setOfflineMode(ctx) {
    const { enabled } = ctx.params;
    
    this.settings.offlineMode = enabled;
    
    this.logger.info(`🔌 Offline mode ${enabled ? 'enabled' : 'disabled'}`);
    
    return {
      success: true,
      offlineMode: enabled
    };
  }

  /**
   * Get authorization status and connectivity info
   */
  async getStatus(ctx) {
    const cloudConnected = await this.checkCloudConnectivity();
    
    return {
      success: true,
      status: {
        offlineMode: this.settings.offlineMode,
        cloudConnected,
        cacheSize: this.permissionCache.size,
        userCacheSize: this.userRoleCache.size,
        localPermissions: this.settings.localPermissions
      }
    };
  }

  /**
   * Clear local cache
   */
  async clearCache(ctx) {
    this.permissionCache.clear();
    this.userRoleCache.clear();
    
    this.logger.info("🗑️ Local authorization cache cleared");
    
    return {
      success: true,
      message: "Cache cleared successfully"
    };
  }

  /**
   * Emergency authorization for critical home automation functions
   */
  async emergencyAuthorize(ctx) {
    const { userId, action, authCode } = ctx.params;
    
    try {
      // Emergency actions that should always be allowed for homeowners/admins
      const userRoles = await this.getUserRolesFromCache(userId);
      const isAuthorized = userRoles.includes("homeowner") || 
                          userRoles.includes("admin") || 
                          this.validateEmergencyCode(authCode);

      this.logger.warn(`🚨 Emergency authorization for ${userId}: ${action} = ${isAuthorized}`);

      return {
        success: true,
        authorized: isAuthorized,
        source: "emergency",
        userId,
        action,
        timestamp: new Date().toISOString()
      };

    } catch (error) {
      this.logger.error("Emergency authorization error:", error);
      return {
        success: false,
        authorized: false,
        error: error.message
      };
    }
  }

  /**
   * Check if a permission is a local-only permission
   */
  isLocalPermission(resource, action) {
    const permissionString = `${resource}:${action}`;
    return this.settings.localPermissions.includes(permissionString) ||
           action === "emergency-stop" ||
           (resource === "security" && action === "alarm-disable");
  }

  /**
   * Check local permission without cloud connectivity
   */
  async checkLocalPermission(userId, resource, action) {
    try {
      // Get user roles from local cache or database
      const userRoles = await this.getUserRolesFromCache(userId);
      
      // Check if user has appropriate role for local permission
      if (userRoles.includes("admin") || userRoles.includes("homeowner")) {
        return true;
      }

      // Check specific local permissions
      const cacheKey = `${userId}:${resource}:${action}`;
      const cachedResult = this.permissionCache.get(cacheKey);
      
      if (cachedResult !== undefined) {
        return cachedResult;
      }

      // Default deny for local permissions if not cached
      return false;

    } catch (error) {
      this.logger.error("Local permission check error:", error);
      return false;
    }
  }

  /**
   * Check offline permission using cached data
   */
  async checkOfflinePermission(userId, resource, action) {
    try {
      const userRoles = await this.getUserRolesFromCache(userId);
      
      // Check offline permissions based on roles
      for (const role of userRoles) {
        const rolePermissions = this.settings.offlinePermissions[role] || [];
        
        // Check for exact match
        if (rolePermissions.includes(`${resource}:${action}`)) {
          return true;
        }
        
        // Check for wildcard permissions
        if (rolePermissions.includes(`${resource}:*`) || rolePermissions.includes("*:*")) {
          return true;
        }
      }

      // Check cached permissions
      const cacheKey = `${userId}:${resource}:${action}`;
      const cachedResult = this.permissionCache.get(cacheKey);
      
      return cachedResult === true;

    } catch (error) {
      this.logger.error("Offline permission check error:", error);
      return false;
    }
  }

  /**
   * Cache authorization result
   */
  cacheAuthorizationResult(userId, resource, action, authorized) {
    if (!this.settings.cacheEnabled) return;
    
    const cacheKey = `${userId}:${resource}:${action}`;
    this.permissionCache.set(cacheKey, authorized);
    
    // Set TTL for cache entry
    setTimeout(() => {
      this.permissionCache.delete(cacheKey);
    }, this.settings.cacheTTL * 1000);
  }

  /**
   * Cache user permissions
   */
  cacheUserPermissions(userId, permissions) {
    if (!this.settings.cacheEnabled) return;
    
    // Cache individual permissions
    permissions.forEach(permission => {
      const cacheKey = `${userId}:${permission.resource}:${permission.action}`;
      this.permissionCache.set(cacheKey, true);
      
      // Set TTL
      setTimeout(() => {
        this.permissionCache.delete(cacheKey);
      }, this.settings.cacheTTL * 1000);
    });
  }

  /**
   * Get user roles from cache or database
   */
  async getUserRolesFromCache(userId) {
    // Check cache first
    let userRoles = this.userRoleCache.get(userId);
    
    if (!userRoles) {
      try {
        // Try to get from database
        const users = database.getCollection("users");
        const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
        
        if (user && user.roles) {
          userRoles = user.roles;
          this.userRoleCache.set(userId, userRoles);
          
          // Set TTL for cache entry
          setTimeout(() => {
            this.userRoleCache.delete(userId);
          }, this.settings.cacheTTL * 1000);
        } else {
          userRoles = ["user"]; // Default role
        }
      } catch (error) {
        this.logger.error("Error getting user roles:", error);
        userRoles = ["user"]; // Default fallback
      }
    }
    
    return userRoles;
  }

  /**
   * Check cloud connectivity
   */
  async checkCloudConnectivity() {
    try {
      // Try to call a simple cloud service action
      const result = await this.broker.call("v1.cloud-authorization.listRoles", {}, { timeout: 3000 });
      
      if (this.settings.offlineMode && result.success) {
        this.settings.offlineMode = false;
        this.logger.info("☁️ Cloud connectivity restored");
      }
      
      return true;
    } catch (error) {
      if (!this.settings.offlineMode) {
        this.settings.offlineMode = true;
        this.logger.warn("🔌 Cloud connectivity lost, switching to offline mode");
      }
      return false;
    }
  }

  /**
   * Validate emergency authorization code
   */
  validateEmergencyCode(authCode) {
    // In production, this should be a secure code from device/app
    const emergencyCode = process.env.EMERGENCY_AUTH_CODE || "HOME911";
    return authCode === emergencyCode;
  }

  /**
   * Handle user login to sync permissions
   */
  handleUserLogin(payload) {
    if (payload.userId) {
      // Async sync of permissions
      this.broker.call("v1.local-authorization.syncPermissions", {
        userId: payload.userId
      }).catch(err => {
        this.logger.warn("Failed to sync permissions on login:", err.message);
      });
    }
  }

  /**
   * Handle role changes to clear cache
   */
  handleUserRolesChanged(payload) {
    if (payload.userId) {
      this.userRoleCache.delete(payload.userId);
      this.logger.info(`🔄 Cleared role cache for user ${payload.userId}`);
    }
  }

  // ==================== Local ABAC Methods ====================

  /**
   * Evaluate local ABAC policies for offline operation
   */
  async evaluateLocalAbacPolicies(ctx) {
    const { userId, resource, action, context = {} } = ctx.params;
    
    try {
      // Use local policies instead of database lookup
      const policies = this.settings.localAbacPolicies.filter(policy => {
        return policy.resource === resource || policy.resource === "*" ||
               (policy.action === action || policy.action === "*");
      });
      
      // Sort by priority
      policies.sort((a, b) => (b.priority || 100) - (a.priority || 100));
      
      // Extract attributes for evaluation
      const userAttributes = await this.extractLocalUserAttributes(userId);
      const resourceAttributes = this.extractLocalResourceAttributes(resource, context);
      const environmentAttributes = this.extractLocalEnvironmentAttributes(context);
      
      const attributes = {
        user: userAttributes,
        resource: resourceAttributes,
        environment: environmentAttributes,
        action: action
      };

      const evaluatedPolicies = [];
      let finalDecision = this.settings.localAbacSettings.defaultDecision;

      // Evaluate each applicable policy
      for (const policy of policies) {
        const policyResult = await this.evaluateLocalAbacCondition(policy.condition, attributes, { userId, resource, action, context });
        
        evaluatedPolicies.push({
          policyId: policy.id,
          name: policy.name,
          resource: policy.resource,
          action: policy.action,
          effect: policy.effect,
          matches: policyResult,
          priority: policy.priority || 100
        });

        // Apply combining algorithm
        if (policyResult) {
          if (this.settings.localAbacSettings.combiningAlgorithm === "deny-overrides" && policy.effect === "DENY") {
            finalDecision = "DENY";
            break;
          } else if (this.settings.localAbacSettings.combiningAlgorithm === "permit-overrides" && policy.effect === "ALLOW") {
            finalDecision = "ALLOW";
          } else if (this.settings.localAbacSettings.combiningAlgorithm === "first-applicable") {
            finalDecision = policy.effect;
            break;
          } else if (policy.effect === "ALLOW") {
            finalDecision = "ALLOW";
          }
        }
      }

      return {
        success: true,
        decision: finalDecision === "ALLOW",
        policies: evaluatedPolicies,
        attributes,
        combiningAlgorithm: this.settings.localAbacSettings.combiningAlgorithm
      };

    } catch (error) {
      this.logger.error("Local ABAC evaluation error:", error);
      return {
        success: false,
        decision: false,
        error: error.message
      };
    }
  }

  /**
   * Evaluate local ABAC condition against attributes
   */
  async evaluateLocalAbacCondition(condition, attributes, context) {
    if (!condition) return false;

    // Handle AND conditions
    if (condition.and) {
      for (const subCondition of condition.and) {
        if (!(await this.evaluateLocalAbacCondition(subCondition, attributes, context))) {
          return false;
        }
      }
      return true;
    }

    // Handle OR conditions
    if (condition.or) {
      for (const subCondition of condition.or) {
        if (await this.evaluateLocalAbacCondition(subCondition, attributes, context)) {
          return true;
        }
      }
      return false;
    }

    // Handle NOT conditions
    if (condition.not) {
      return !(await this.evaluateLocalAbacCondition(condition.not, attributes, context));
    }

    // Handle specific attribute conditions
    for (const [key, value] of Object.entries(condition)) {
      if (!this.evaluateLocalAttributeCondition(key, value, attributes, context)) {
        return false;
      }
    }

    return true;
  }

  /**
   * Evaluate specific attribute condition for local policies
   */
  evaluateLocalAttributeCondition(attributeName, condition, attributes, context) {
    let attributeValue;

    // Get attribute value based on attribute name
    switch (attributeName) {
      case "resource":
        attributeValue = context.resource;
        break;
      case "action":
        attributeValue = context.action;
        break;
      case "userRole":
        attributeValue = attributes.user.roles;
        break;
      case "userId":
        attributeValue = context.userId;
        break;
      case "time":
        attributeValue = new Date().toTimeString().slice(0, 5); // HH:MM format
        break;
      case "dayOfWeek":
        attributeValue = new Date().toLocaleDateString('en-US', { weekday: 'lowercase' });
        break;
      case "userLocation":
        attributeValue = attributes.user.location || "unknown";
        break;
      case "deviceOwner":
        attributeValue = attributes.resource.owner;
        break;
      case "emergencyMode":
        attributeValue = attributes.environment.emergencyMode || false;
        break;
      case "offlineMode":
        attributeValue = attributes.environment.offlineMode || false;
        break;
      default:
        attributeValue = attributes.user[attributeName] || 
                        attributes.resource[attributeName] || 
                        attributes.environment[attributeName];
        break;
    }

    // Evaluate condition operators (same logic as cloud service)
    if (typeof condition === "string" || typeof condition === "number" || typeof condition === "boolean") {
      return attributeValue === condition;
    }

    if (condition.equals) {
      if (condition.equals === "userId") {
        return attributeValue === context.userId;
      }
      return attributeValue === condition.equals;
    }

    if (condition.in) {
      return Array.isArray(attributeValue) 
        ? condition.in.some(val => attributeValue.includes(val))
        : condition.in.includes(attributeValue);
    }

    if (condition.notIn) {
      return Array.isArray(attributeValue)
        ? !condition.notIn.some(val => attributeValue.includes(val))
        : !condition.notIn.includes(attributeValue);
    }

    if (condition.before) {
      return attributeValue < condition.before;
    }

    if (condition.after) {
      return attributeValue > condition.after;
    }

    if (condition.contains && Array.isArray(attributeValue)) {
      return attributeValue.includes(condition.contains);
    }

    return false;
  }

  /**
   * Extract user attributes for local ABAC evaluation
   */
  async extractLocalUserAttributes(userId) {
    try {
      // Get from cache first, then fallback to database
      const userRoles = await this.getUserRolesFromCache(userId);
      
      // Try to get more user info from cache/database
      let userInfo = { roles: userRoles };
      try {
        const users = database.getCollection("users");
        const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
        if (user) {
          userInfo = {
            id: userId,
            email: user.email,
            roles: userRoles,
            location: user.location || "home", // Default to home for local access
            department: user.department,
            preferences: user.preferences || {}
          };
        }
      } catch (error) {
        this.logger.warn("Could not fetch full user info for local ABAC:", error.message);
      }

      return userInfo;
    } catch (error) {
      this.logger.error("Error extracting local user attributes:", error);
      return { roles: ["user"], location: "home" };
    }
  }

  /**
   * Extract resource attributes for local ABAC evaluation
   */
  extractLocalResourceAttributes(resource, context) {
    const resourceData = context.resourceData || {};
    
    return {
      type: resource,
      owner: resourceData.owner,
      location: resourceData.location || "local",
      sensitivity: resourceData.sensitivity || "normal",
      tags: resourceData.tags || [],
      isLocal: true
    };
  }

  /**
   * Extract environment attributes for local ABAC evaluation
   */
  extractLocalEnvironmentAttributes(context) {
    const now = new Date();
    
    return {
      currentTime: now.toTimeString().slice(0, 5),
      currentDate: now.toISOString().slice(0, 10),
      dayOfWeek: now.toLocaleDateString('en-US', { weekday: 'lowercase' }),
      emergencyMode: context.emergencyMode || false,
      offlineMode: context.offlineMode || this.settings.offlineMode,
      networkType: "local",
      location: "home"
    };
  }

  /**
   * Combine local RBAC and ABAC decisions
   */
  combineLocalDecisions(rbacResult, abacResult, context) {
    // Emergency mode always takes precedence
    if (context.emergencyMode) {
      return true;
    }

    // ABAC denial takes precedence
    if (abacResult === false) {
      return false;
    }

    // If ABAC allows or is neutral, check RBAC
    return rbacResult && abacResult !== false;
  }
}

module.exports = LocalAuthorizationService;
