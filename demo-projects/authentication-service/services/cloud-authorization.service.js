const { Service } = require("moleculer");
const { MoleculerError } = require("moleculer").Errors;
const database = require("../utils/database");

class CloudAuthorizationService extends Service {
  constructor(broker) {
    super(broker);

    this.parseServiceSchema({
      name: "cloud-authorization",
      version: 1,

      settings: {
        // Default system roles and permissions
        systemRoles: [
          {
            name: "admin",
            description: "Full system administrator",
            permissions: ["*:*"] // All permissions
          },
          {
            name: "user",
            description: "Standard user",
            permissions: ["device:read", "room:read"]
          },
          {
            name: "homeowner",
            description: "Home owner with device management rights",
            permissions: ["device:*", "room:*", "automation:*"]
          }
        ],
        systemPermissions: [
          // Device permissions
          { name: "device:read", resource: "device", action: "read", description: "Read device information" },
          { name: "device:write", resource: "device", action: "write", description: "Control devices" },
          {
            name: "device:write:own",
            resource: "device",
            action: "write",
            description: "Control own devices (Attribute-Based)",
            conditions: {
              "user.id": "resource.ownerId"
            }
          },
          { name: "device:admin", resource: "device", action: "admin", description: "Manage device settings" },
          { name: "device:*", resource: "device", action: "*", description: "All device permissions" },
          
          // Room permissions
          { name: "room:read", resource: "room", action: "read", description: "View room information" },
          { name: "room:write", resource: "room", action: "write", description: "Modify room settings" },
          { name: "room:admin", resource: "room", action: "admin", description: "Manage room configuration" },
          { name: "room:*", resource: "room", action: "*", description: "All room permissions" },
          
          // Automation permissions
          { name: "automation:read", resource: "automation", action: "read", description: "View automations" },
          { name: "automation:write", resource: "automation", action: "write", description: "Create/edit automations" },
          { name: "automation:execute", resource: "automation", action: "execute", description: "Run automations" },
          { name: "automation:*", resource: "automation", action: "*", description: "All automation permissions" },
          
          // System permissions
          { name: "system:read", resource: "system", action: "read", description: "View system status" },
          { name: "system:admin", resource: "system", action: "admin", description: "System administration" },
          { name: "*:*", resource: "*", action: "*", description: "All permissions" }
        ],
        
        // ABAC (Attribute-Based Access Control) Policies
        abacPolicies: [
          {
            id: "time-based-access",
            name: "Time-based Access Control",
            description: "Restrict device control during certain hours",
            resource: "device",
            action: "write",
            effect: "DENY",
            priority: 100,
            condition: {
              and: [
                { 
                  or: [
                    { time: { before: "06:00" } },
                    { time: { after: "23:00" } }
                  ]
                },
                { userRole: { notIn: ["admin", "homeowner"] } }
              ]
            }
          },
          {
            id: "location-based-access",
            name: "Location-based Access Control",
            description: "Restrict security admin access based on user location",
            resource: "security",
            action: "admin",
            effect: "DENY",
            priority: 200,
            condition: {
              userLocation: { notIn: ["home", "trusted"] }
            }
          },
          {
            id: "device-ownership",
            name: "Device Ownership Control",
            description: "Users can only control devices they own",
            resource: "device",
            action: "*",
            effect: "ALLOW",
            priority: 300,
            condition: {
              and: [
                { action: { in: ["read", "write"] } },
                { deviceOwner: { equals: "userId" } }
              ]
            }
          },
          {
            id: "emergency-override",
            name: "Emergency Override Policy",
            description: "Allow emergency actions regardless of other restrictions",
            resource: "*",
            action: "*",
            effect: "ALLOW",
            priority: 1000,
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
            id: "business-hours-automation",
            name: "Business Hours Automation",
            description: "Allow automation execution only during business hours for non-admins",
            resource: "automation",
            action: "execute",
            effect: "DENY",
            priority: 150,
            condition: {
              and: [
                { userRole: { notIn: ["admin", "homeowner"] } },
                {
                  or: [
                    { dayOfWeek: { in: ["saturday", "sunday"] } },
                    { time: { before: "08:00" } },
                    { time: { after: "18:00" } }
                  ]
                }
              ]
            }
          },
          {
            id: "guest-read-only",
            name: "Guest Read-Only Access",
            description: "Guest users can only read devices and rooms",
            resource: "*",
            action: "*",
            effect: "DENY",
            priority: 400,
            condition: {
              and: [
                { userRole: { in: ["guest"] } },
                { action: { notIn: ["read"] } }
              ]
            }
          },
          {
            id: "maintenance-mode-restriction",
            name: "Maintenance Mode Restriction",
            description: "Only admins can perform actions during maintenance mode",
            resource: "*",
            action: "*",
            effect: "DENY",
            priority: 500,
            condition: {
              and: [
                { maintenanceMode: true },
                { userRole: { notIn: ["admin"] } },
                { action: { notIn: ["read", "emergency-stop"] } }
              ]
            }
          }
        ],
        
        // ABAC evaluation settings
        abacSettings: {
          enabled: true,
          defaultDecision: "DENY", // Default decision when no policy matches
          policyEvaluationOrder: "priority", // priority | creation | alphabetical
          combiningAlgorithm: "deny-overrides" // deny-overrides | permit-overrides | first-applicable
        }
      },

      dependencies: [],

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
        createPermission: {
          params: {
            name: { type: "string" },
            resource: { type: "string" },
            action: { type: "string" },
            description: { type: "string", optional: true }
          },
          handler: this.createPermission
        },
        createRole: {
          params: {
            name: { type: "string" },
            description: { type: "string", optional: true },
            permissions: { type: "array", items: "string", optional: true }
          },
          handler: this.createRole
        },
        assignPermissionsToRole: {
          params: {
            roleId: { type: "string" },
            permissionIds: { type: "array", items: "string" }
          },
          handler: this.assignPermissionsToRole
        },
        assignRolesToUser: {
          params: {
            userId: { type: "string" },
            roleIds: { type: "array", items: "string" }
          },
          handler: this.assignRolesToUser
        },
        getUserPermissions: {
          params: {
            userId: { type: "string" }
          },
          handler: this.getUserPermissions
        },
        listPermissions: this.listPermissions,
        listRoles: this.listRoles,
        
        // ABAC Actions
        createAbacPolicy: {
          params: {
            name: { type: "string" },
            description: { type: "string", optional: true },
            resource: { type: "string" },
            action: { type: "string" },
            effect: { type: "string", enum: ["ALLOW", "DENY"] },
            condition: { type: "object" },
            priority: { type: "number", optional: true, default: 100 }
          },
          handler: this.createAbacPolicy
        },
        updateAbacPolicy: {
          params: {
            policyId: { type: "string" },
            name: { type: "string", optional: true },
            description: { type: "string", optional: true },
            resource: { type: "string", optional: true },
            action: { type: "string", optional: true },
            effect: { type: "string", enum: ["ALLOW", "DENY"], optional: true },
            condition: { type: "object", optional: true },
            priority: { type: "number", optional: true }
          },
          handler: this.updateAbacPolicy
        },
        deleteAbacPolicy: {
          params: {
            policyId: { type: "string" }
          },
          handler: this.deleteAbacPolicy
        },
        listAbacPolicies: this.listAbacPolicies,
        evaluateAbacPolicies: {
          params: {
            userId: { type: "string" },
            resource: { type: "string" },
            action: { type: "string" },
            context: { type: "object", optional: true }
          },
          handler: this.evaluateAbacPolicies
        },
        
        // 3-Step Filtering Actions (for demonstration/debugging)
        performRoleBasedFiltering: {
          params: {
            userId: { type: "string" }
          },
          handler: this.performRoleBasedFiltering
        },
        performActionBasedFiltering: {
          params: {
            userRoles: { type: "array", items: "string" },
            resource: { type: "string" },
            action: { type: "string" }
          },
          handler: this.performActionBasedFiltering
        },
        performAttributeBasedEvaluation: {
          params: {
            userId: { type: "string" },
            resource: { type: "string" },
            action: { type: "string" },
            context: { type: "object", optional: true },
            applicableRules: { type: "object" }
          },
          handler: this.performAttributeBasedEvaluation
        }
      },

      methods: {
        checkPermission: this.checkPermission,
        getUserPermissions: this.getUserPermissionsMethod,
        initializeSystemPermissions: this.initializeSystemPermissions,
        initializeSystemRoles: this.initializeSystemRoles,
        
        // ABAC Methods
        evaluateAbacCondition: this.evaluateAbacCondition,
        extractUserAttributes: this.extractUserAttributes,
        extractResourceAttributes: this.extractResourceAttributes,
        extractEnvironmentAttributes: this.extractEnvironmentAttributes,
        combineDecisions: this.combineDecisions,
        initializeAbacPolicies: this.initializeAbacPolicies,
        
        // 3-Step Filtering Methods
        performRoleBasedFiltering: this.performRoleBasedFiltering,
        performActionBasedFiltering: this.performActionBasedFiltering,
        performAttributeBasedEvaluation: this.performAttributeBasedEvaluation
      },

      created: this.serviceCreated,
      started: this.serviceStarted
    });
  }

  async serviceCreated() {
    this.logger.info("🛡️ Cloud Authorization Service created");
  }

  async serviceStarted() {
    // Initialize collections with indexes
    const permissions = database.getCollection("permissions");
    const roles = database.getCollection("roles");
    const abacPolicies = database.getCollection("abacPolicies");
    
    await permissions.createIndex({ name: 1 }, { unique: true });
    await permissions.createIndex({ resource: 1, action: 1 });
    await roles.createIndex({ name: 1 }, { unique: true });
    await abacPolicies.createIndex({ name: 1 }, { unique: true });
    await abacPolicies.createIndex({ priority: -1 });
    
    // Create system permissions if they don't exist
    await this.initializeSystemPermissions();
    
    // Create system roles if they don't exist
    await this.initializeSystemRoles();
    
    // Initialize ABAC policies
    await this.initializeAbacPolicies();
    
    this.logger.info("🛡️ Cloud Authorization Service started with RBAC + ABAC support");
  }

  /**
   * Enhanced authorization with proper 3-step filtering: Role → Action → Attribute
   */
  async authorize(ctx) {
    const { userId, resource, action, context = {} } = ctx.params;
    
    try {
      // STEP 1: Role-Based Filtering (The Broad Stroke)
      // Get user's roles and filter the universe of applicable rules
      const roleFilterResult = await this.performRoleBasedFiltering(userId);
      
      if (!roleFilterResult.success) {
        return {
          success: false,
          authorized: false,
          error: "User not found or has no roles",
          step: "role-filtering"
        };
      }

      // STEP 2: Action-Based Filtering
      // From role-specific rules, get only rules for the specific action
      const actionFilterResult = await this.performActionBasedFiltering(
        roleFilterResult.userRoles, 
        resource, 
        action
      );

      if (!actionFilterResult.hasApplicableRules) {
        return {
          success: true,
          authorized: false,
          userId,
          resource,
          action,
          context,
          reason: "No rules found for this action with user's roles",
          evaluationDetails: {
            step1_roles: roleFilterResult.userRoles,
            step2_action_rules: actionFilterResult.applicableRules,
            step3_attribute_check: "skipped - no applicable rules",
            final: false
          }
        };
      }

      // STEP 3: Attribute-Based Evaluation (The Fine-Grained Check)
      // Evaluate attribute-based conditions on the specific resource
      const attributeEvalResult = await this.performAttributeBasedEvaluation(
        userId,
        resource, 
        action,
        context,
        actionFilterResult.applicableRules
      );

      return {
        success: true,
        authorized: attributeEvalResult.authorized,
        userId,
        resource,
        action,
        context,
        evaluationDetails: {
          step1_roles: roleFilterResult.userRoles,
          step2_action_rules: actionFilterResult.applicableRules,
          step3_attribute_check: attributeEvalResult,
          final: attributeEvalResult.authorized
        }
      };

    } catch (error) {
      this.logger.error("Authorization error:", error);
      return {
        success: false,
        authorized: false,
        error: error.message
      };
    }
  }

  /**
   * Create a new permission
   */
  async createPermission(ctx) {
    const permissionData = ctx.params;
    
    try {
      const permissions = database.getCollection("permissions");
      
      // Check if permission already exists
      const existing = await permissions.findOne({ name: permissionData.name });
      if (existing) {
        throw new MoleculerError("Permission already exists", 409, "PERMISSION_EXISTS");
      }

      permissionData.createdAt = new Date();
      permissionData.updatedAt = new Date();

      const result = await permissions.insertOne(permissionData);
      
      const permission = { ...permissionData, id: result.insertedId.toString() };
      
      this.logger.info(`🔐 Permission created: ${permission.name}`);
      
      return {
        success: true,
        permission
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Create permission error:", error);
      throw new MoleculerError("Failed to create permission", 500, "CREATE_PERMISSION_FAILED");
    }
  }

  /**
   * Create a new role
   */
  async createRole(ctx) {
    const roleData = ctx.params;
    
    try {
      const roles = database.getCollection("roles");
      
      // Check if role already exists
      const existing = await roles.findOne({ name: roleData.name });
      if (existing) {
        throw new MoleculerError("Role already exists", 409, "ROLE_EXISTS");
      }

      roleData.createdAt = new Date();
      roleData.updatedAt = new Date();

      const result = await roles.insertOne(roleData);
      
      const role = { ...roleData, id: result.insertedId.toString() };
      
      this.logger.info(`👥 Role created: ${role.name}`);
      
      return {
        success: true,
        role
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Create role error:", error);
      throw new MoleculerError("Failed to create role", 500, "CREATE_ROLE_FAILED");
    }
  }

  /**
   * Assign permissions to a role
   */
  async assignPermissionsToRole(ctx) {
    const { roleId, permissionIds } = ctx.params;
    
    try {
      const roles = database.getCollection("roles");
      const permissions = database.getCollection("permissions");
      
      // Verify role exists
      const role = await roles.findOne({ _id: database.getDatabase().ObjectId(roleId) });
      if (!role) {
        throw new MoleculerError("Role not found", 404, "ROLE_NOT_FOUND");
      }

      // Verify all permissions exist
      const permissionObjects = await permissions.find({
        _id: { $in: permissionIds.map(id => database.getDatabase().ObjectId(id)) }
      }).toArray();

      if (permissionObjects.length !== permissionIds.length) {
        throw new MoleculerError("One or more permissions not found", 404, "PERMISSION_NOT_FOUND");
      }

      // Update role with new permissions
      await roles.updateOne(
        { _id: role._id },
        {
          $set: {
            permissions: permissionIds,
            updatedAt: new Date()
          }
        }
      );

      this.logger.info(`🔗 Permissions assigned to role: ${role.name}`);

      return {
        success: true,
        message: "Permissions assigned successfully"
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Assign permissions error:", error);
      throw new MoleculerError("Failed to assign permissions", 500, "ASSIGN_PERMISSIONS_FAILED");
    }
  }

  /**
   * Assign roles to a user
   */
  async assignRolesToUser(ctx) {
    const { userId, roleIds } = ctx.params;
    
    try {
      const users = database.getCollection("users");
      const roles = database.getCollection("roles");
      
      // Verify user exists
      const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
      if (!user) {
        throw new MoleculerError("User not found", 404, "USER_NOT_FOUND");
      }

      // Verify all roles exist
      const roleObjects = await roles.find({
        _id: { $in: roleIds.map(id => database.getDatabase().ObjectId(id)) }
      }).toArray();

      if (roleObjects.length !== roleIds.length) {
        throw new MoleculerError("One or more roles not found", 404, "ROLE_NOT_FOUND");
      }

      // Update user with new roles
      await users.updateOne(
        { _id: user._id },
        {
          $set: {
            roles: roleObjects.map(role => role.name),
            updatedAt: new Date()
          }
        }
      );

      this.logger.info(`👤 Roles assigned to user: ${user.email}`);

      return {
        success: true,
        message: "Roles assigned successfully"
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Assign roles error:", error);
      throw new MoleculerError("Failed to assign roles", 500, "ASSIGN_ROLES_FAILED");
    }
  }

  /**
   * Get user permissions action
   */
  async getUserPermissions(ctx) {
    const { userId } = ctx.params;
    
    try {
      const userPermissions = await this.getUserPermissionsMethod(userId);
      
      return {
        success: true,
        userId,
        permissions: userPermissions
      };

    } catch (error) {
      this.logger.error("Get user permissions error:", error);
      throw new MoleculerError("Failed to get user permissions", 500, "GET_PERMISSIONS_FAILED");
    }
  }

  /**
   * List all permissions
   */
  async listPermissions(ctx) {
    try {
      const permissions = database.getCollection("permissions");
      const allPermissions = await permissions.find({}).toArray();
      
      return {
        success: true,
        permissions: allPermissions.map(p => ({
          ...p,
          id: p._id.toString()
        }))
      };

    } catch (error) {
      this.logger.error("List permissions error:", error);
      throw new MoleculerError("Failed to list permissions", 500, "LIST_PERMISSIONS_FAILED");
    }
  }

  /**
   * List all roles
   */
  async listRoles(ctx) {
    try {
      const roles = database.getCollection("roles");
      const allRoles = await roles.find({}).toArray();
      
      return {
        success: true,
        roles: allRoles.map(r => ({
          ...r,
          id: r._id.toString()
        }))
      };

    } catch (error) {
      this.logger.error("List roles error:", error);
      throw new MoleculerError("Failed to list roles", 500, "LIST_ROLES_FAILED");
    }
  }

  /**
   * Check if user has permission for specific resource and action
   */
  async checkPermission(userId, resource, action, context = {}) {
    try {
      const userPermissions = await this.getUserPermissionsMethod(userId);
      
      // Check for exact match
      const exactMatch = userPermissions.some(perm => 
        perm.resource === resource && perm.action === action
      );
      
      if (exactMatch) return true;
      
      // Check for wildcard permissions
      const wildcardMatch = userPermissions.some(perm => 
        (perm.resource === "*" || perm.resource === resource) &&
        (perm.action === "*")
      );
      
      if (wildcardMatch) return true;
      
      // Check for resource-specific wildcard
      const resourceWildcard = userPermissions.some(perm => 
        perm.resource === resource && perm.action === "*"
      );
      
      return resourceWildcard;

    } catch (error) {
      this.logger.error("Check permission error:", error);
      return false;
    }
  }

  /**
   * Get all permissions for a user based on their roles
   */
  async getUserPermissionsMethod(userId) {
    const users = database.getCollection("users");
    const roles = database.getCollection("roles");
    const permissions = database.getCollection("permissions");
    
    // Get user
    const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
    if (!user) {
      throw new Error("User not found");
    }

    // Get user's roles
    const userRoles = await roles.find({ name: { $in: user.roles } }).toArray();
    
    // Collect all permission IDs from user's roles
    const permissionIds = [];
    userRoles.forEach(role => {
      if (role.permissions) {
        permissionIds.push(...role.permissions);
      }
    });

    // Get unique permission objects
    const uniquePermissionIds = [...new Set(permissionIds)];
    const userPermissions = await permissions.find({
      _id: { $in: uniquePermissionIds.map(id => database.getDatabase().ObjectId(id)) }
    }).toArray();

    return userPermissions;
  }

  /**
   * Initialize system permissions
   */
  async initializeSystemPermissions() {
    const permissions = database.getCollection("permissions");
    
    for (const permData of this.settings.systemPermissions) {
      const existing = await permissions.findOne({ name: permData.name });
      if (!existing) {
        await permissions.insertOne({
          ...permData,
          createdAt: new Date(),
          updatedAt: new Date()
        });
        this.logger.info(`🔐 System permission created: ${permData.name}`);
      }
    }
  }

  /**
   * Initialize system roles
   */
  async initializeSystemRoles() {
    const roles = database.getCollection("roles");
    const permissions = database.getCollection("permissions");
    
    for (const roleData of this.settings.systemRoles) {
      const existing = await roles.findOne({ name: roleData.name });
      if (!existing) {
        // Get permission IDs for this role
        const rolePermissions = await permissions.find({
          name: { $in: roleData.permissions }
        }).toArray();
        
        await roles.insertOne({
          name: roleData.name,
          description: roleData.description,
          permissions: rolePermissions.map(p => p._id.toString()),
          isSystemRole: true,
          createdAt: new Date(),
          updatedAt: new Date()
        });
        
        this.logger.info(`👥 System role created: ${roleData.name}`);
      }
    }
  }

  // ==================== ABAC Methods ====================

  /**
   * Create a new ABAC policy
   */
  async createAbacPolicy(ctx) {
    const policyData = ctx.params;
    
    try {
      const abacPolicies = database.getCollection("abacPolicies");
      
      // Check if policy already exists
      const existing = await abacPolicies.findOne({ name: policyData.name });
      if (existing) {
        throw new MoleculerError("ABAC policy already exists", 409, "POLICY_EXISTS");
      }

      const policy = {
        ...policyData,
        id: database.getDatabase().ObjectId().toString(),
        createdAt: new Date(),
        updatedAt: new Date(),
        enabled: true
      };

      await abacPolicies.insertOne(policy);
      
      this.logger.info(`🔒 ABAC Policy created: ${policy.name}`);
      
      return {
        success: true,
        policy
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Create ABAC policy error:", error);
      throw new MoleculerError("Failed to create ABAC policy", 500, "CREATE_POLICY_FAILED");
    }
  }

  /**
   * Update an existing ABAC policy
   */
  async updateAbacPolicy(ctx) {
    const { policyId, ...updateData } = ctx.params;
    
    try {
      const abacPolicies = database.getCollection("abacPolicies");
      
      const result = await abacPolicies.updateOne(
        { _id: database.getDatabase().ObjectId(policyId) },
        {
          $set: {
            ...updateData,
            updatedAt: new Date()
          }
        }
      );

      if (result.matchedCount === 0) {
        throw new MoleculerError("ABAC policy not found", 404, "POLICY_NOT_FOUND");
      }

      this.logger.info(`🔒 ABAC Policy updated: ${policyId}`);
      
      return {
        success: true,
        message: "Policy updated successfully"
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Update ABAC policy error:", error);
      throw new MoleculerError("Failed to update ABAC policy", 500, "UPDATE_POLICY_FAILED");
    }
  }

  /**
   * Delete an ABAC policy
   */
  async deleteAbacPolicy(ctx) {
    const { policyId } = ctx.params;
    
    try {
      const abacPolicies = database.getCollection("abacPolicies");
      
      const result = await abacPolicies.deleteOne({
        _id: database.getDatabase().ObjectId(policyId)
      });

      if (result.deletedCount === 0) {
        throw new MoleculerError("ABAC policy not found", 404, "POLICY_NOT_FOUND");
      }

      this.logger.info(`🗑️ ABAC Policy deleted: ${policyId}`);
      
      return {
        success: true,
        message: "Policy deleted successfully"
      };

    } catch (error) {
      if (error instanceof MoleculerError) throw error;
      this.logger.error("Delete ABAC policy error:", error);
      throw new MoleculerError("Failed to delete ABAC policy", 500, "DELETE_POLICY_FAILED");
    }
  }

  /**
   * List all ABAC policies
   */
  async listAbacPolicies(ctx) {
    try {
      const abacPolicies = database.getCollection("abacPolicies");
      const policies = await abacPolicies.find({}).sort({ priority: -1 }).toArray();
      
      return {
        success: true,
        policies: policies.map(p => ({
          ...p,
          id: p._id.toString()
        }))
      };

    } catch (error) {
      this.logger.error("List ABAC policies error:", error);
      throw new MoleculerError("Failed to list ABAC policies", 500, "LIST_POLICIES_FAILED");
    }
  }

  /**
   * Evaluate ABAC policies for authorization request
   */
  async evaluateAbacPolicies(ctx) {
    const { userId, resource, action, context = {} } = ctx.params;
    
    try {
      const abacPolicies = database.getCollection("abacPolicies");
      
      // Find applicable policies based on resource and action
      const query = {
        enabled: true,
        $or: [
          { resource: resource, action: action },
          { resource: resource, action: "*" },
          { resource: "*", action: action },
          { resource: "*", action: "*" }
        ]
      };
      
      const policies = await abacPolicies.find(query).sort({ priority: -1 }).toArray();
      
      // Extract attributes for evaluation
      const userAttributes = await this.extractUserAttributes(userId);
      const resourceAttributes = await this.extractResourceAttributes(resource, context);
      const environmentAttributes = this.extractEnvironmentAttributes(context);
      
      const attributes = {
        user: userAttributes,
        resource: resourceAttributes,
        environment: environmentAttributes,
        action: action
      };

      const evaluatedPolicies = [];
      let finalDecision = this.settings.abacSettings.defaultDecision;

      // Evaluate each applicable policy
      for (const policy of policies) {
        const policyResult = await this.evaluateAbacCondition(policy.condition, attributes, { userId, resource, action, context });
        
        evaluatedPolicies.push({
          policyId: policy._id.toString(),
          name: policy.name,
          resource: policy.resource,
          action: policy.action,
          effect: policy.effect,
          matches: policyResult,
          priority: policy.priority || 100
        });

        // Apply combining algorithm
        if (policyResult) {
          if (this.settings.abacSettings.combiningAlgorithm === "deny-overrides" && policy.effect === "DENY") {
            finalDecision = "DENY";
            break;
          } else if (this.settings.abacSettings.combiningAlgorithm === "permit-overrides" && policy.effect === "ALLOW") {
            finalDecision = "ALLOW";
          } else if (this.settings.abacSettings.combiningAlgorithm === "first-applicable") {
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
        combiningAlgorithm: this.settings.abacSettings.combiningAlgorithm
      };

    } catch (error) {
      this.logger.error("ABAC evaluation error:", error);
      return {
        success: false,
        decision: false,
        error: error.message
      };
    }
  }

  /**
   * Evaluate ABAC condition against attributes
   */
  async evaluateAbacCondition(condition, attributes, context) {
    if (!condition) return false;

    // Handle AND conditions
    if (condition.and) {
      for (const subCondition of condition.and) {
        if (!(await this.evaluateAbacCondition(subCondition, attributes, context))) {
          return false;
        }
      }
      return true;
    }

    // Handle OR conditions
    if (condition.or) {
      for (const subCondition of condition.or) {
        if (await this.evaluateAbacCondition(subCondition, attributes, context)) {
          return true;
        }
      }
      return false;
    }

    // Handle NOT conditions
    if (condition.not) {
      return !(await this.evaluateAbacCondition(condition.not, attributes, context));
    }

    // Handle specific attribute conditions
    for (const [key, value] of Object.entries(condition)) {
      if (!this.evaluateAttributeCondition(key, value, attributes, context)) {
        return false;
      }
    }

    return true;
  }

  /**
   * Evaluate specific attribute condition
   */
  evaluateAttributeCondition(attributeName, condition, attributes, context) {
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
      case "maintenanceMode":
        attributeValue = attributes.environment.maintenanceMode || false;
        break;
      default:
        // Check if attribute exists in any of the attribute categories
        attributeValue = attributes.user[attributeName] || 
                        attributes.resource[attributeName] || 
                        attributes.environment[attributeName];
        break;
    }

    // Evaluate condition operators
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
   * Extract user attributes for ABAC evaluation
   */
  async extractUserAttributes(userId) {
    try {
      const users = database.getCollection("users");
      const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
      
      if (!user) {
        return { roles: ["user"], location: "unknown" };
      }

      return {
        id: userId,
        email: user.email,
        roles: user.roles || ["user"],
        location: user.location || "unknown",
        department: user.department,
        securityClearance: user.securityClearance,
        lastLogin: user.lastLogin,
        preferences: user.preferences || {}
      };
    } catch (error) {
      this.logger.error("Error extracting user attributes:", error);
      return { roles: ["user"], location: "unknown" };
    }
  }

  /**
   * Extract resource attributes for ABAC evaluation
   */
  async extractResourceAttributes(resource, context) {
    try {
      // This would typically query a resources collection
      // For now, we'll use context data and some defaults
      const resourceData = context.resourceData || {};
      
      return {
        type: resource,
        owner: resourceData.owner,
        location: resourceData.location || "unknown",
        sensitivity: resourceData.sensitivity || "normal",
        tags: resourceData.tags || [],
        createdAt: resourceData.createdAt,
        lastModified: resourceData.lastModified
      };
    } catch (error) {
      this.logger.error("Error extracting resource attributes:", error);
      return { type: resource };
    }
  }

  /**
   * Extract environment attributes for ABAC evaluation
   */
  extractEnvironmentAttributes(context) {
    const now = new Date();
    
    return {
      currentTime: now.toTimeString().slice(0, 5),
      currentDate: now.toISOString().slice(0, 10),
      dayOfWeek: now.toLocaleDateString('en-US', { weekday: 'lowercase' }),
      ipAddress: context.ipAddress || "unknown",
      userAgent: context.userAgent || "unknown",
      emergencyMode: context.emergencyMode || false,
      maintenanceMode: context.maintenanceMode || false,
      networkType: context.networkType || "unknown"
    };
  }

  /**
   * Combine RBAC and ABAC decisions
   */
  combineDecisions(rbacResult, abacResult, context) {
    // If emergency mode, allow access
    if (context.emergencyMode) {
      return true;
    }

    // ABAC takes precedence - if ABAC explicitly denies, deny access
    if (abacResult === false) {
      return false;
    }

    // If ABAC allows or is neutral, check RBAC
    return rbacResult && abacResult !== false;
  }

  /**
   * Initialize ABAC policies from settings
   */
  async initializeAbacPolicies() {
    const abacPolicies = database.getCollection("abacPolicies");
    
    for (const policyData of this.settings.abacPolicies) {
      const existing = await abacPolicies.findOne({ id: policyData.id });
      if (!existing) {
        await abacPolicies.insertOne({
          ...policyData,
          _id: database.getDatabase().ObjectId(),
          enabled: true,
          createdAt: new Date(),
          updatedAt: new Date()
        });
        this.logger.info(`🔒 ABAC Policy initialized: ${policyData.name}`);
      }
    }
  }

  // ==================== 3-Step Filtering Methods ====================

  /**
   * STEP 1: Role-Based Filtering (The Broad Stroke)
   * Get user's roles and filter the universe of applicable rules
   */
  async performRoleBasedFiltering(userId) {
    try {
      const users = database.getCollection("users");
      const user = await users.findOne({ _id: database.getDatabase().ObjectId(userId) });
      
      if (!user) {
        return {
          success: false,
          error: "User not found"
        };
      }

      if (!user.roles || user.roles.length === 0) {
        return {
          success: false,
          error: "User has no roles assigned"
        };
      }

      this.logger.info(`🎭 Step 1 - Role filtering for user ${userId}: roles = [${user.roles.join(', ')}]`);

      return {
        success: true,
        userRoles: user.roles,
        userId: userId
      };

    } catch (error) {
      this.logger.error("Role-based filtering error:", error);
      return {
        success: false,
        error: error.message
      };
    }
  }

  /**
   * STEP 2: Action-Based Filtering
   * From role-specific rules, get only rules for the specific action
   */
  async performActionBasedFiltering(userRoles, resource, action) {
    try {
      const roles = database.getCollection("roles");
      const permissions = database.getCollection("permissions");
      const abacPolicies = database.getCollection("abacPolicies");

      // Get role-specific RBAC permissions
      const userRoleObjects = await roles.find({ name: { $in: userRoles } }).toArray();
      
      const permissionIds = [];
      userRoleObjects.forEach(role => {
        if (role.permissions) {
          permissionIds.push(...role.permissions);
        }
      });

      // Get permissions that match the specific resource+action
      const uniquePermissionIds = [...new Set(permissionIds)];
      const rolePermissions = await permissions.find({
        _id: { $in: uniquePermissionIds.map(id => database.getDatabase().ObjectId(id)) },
        $or: [
          { resource: resource, action: action },
          { resource: resource, action: "*" },
          { resource: "*", action: action },
          { resource: "*", action: "*" }
        ]
      }).toArray();

      // Get ABAC policies that match resource+action and are applicable to user roles
      const abacRules = await abacPolicies.find({
        enabled: true,
        $or: [
          { resource: resource, action: action },
          { resource: resource, action: "*" },
          { resource: "*", action: action },
          { resource: "*", action: "*" }
        ]
      }).toArray();

      // Filter ABAC policies that might apply to these roles (basic pre-filtering)
      const roleApplicableAbacRules = [];
      for (const policy of abacRules) {
        // Check if policy condition might apply to any of the user's roles
        const mightApply = await this.policyMightApplyToRoles(policy, userRoles);
        if (mightApply) {
          roleApplicableAbacRules.push(policy);
        }
      }

      const hasApplicableRules = rolePermissions.length > 0 || roleApplicableAbacRules.length > 0;

      this.logger.info(`🎯 Step 2 - Action filtering for ${resource}:${action}: found ${rolePermissions.length} RBAC rules, ${roleApplicableAbacRules.length} ABAC rules`);

      return {
        hasApplicableRules,
        applicableRules: {
          rbacPermissions: rolePermissions,
          abacPolicies: roleApplicableAbacRules,
          userRoles: userRoles
        }
      };

    } catch (error) {
      this.logger.error("Action-based filtering error:", error);
      return {
        hasApplicableRules: false,
        error: error.message
      };
    }
  }

  /**
   * STEP 3: Attribute-Based Evaluation (The Fine-Grained Check)
   * Evaluate attribute-based conditions on the specific resource
   */
  async performAttributeBasedEvaluation(userId, resource, action, context, applicableRules) {
    try {
      // Extract attributes for evaluation
      const userAttributes = await this.extractUserAttributes(userId);
      const resourceAttributes = await this.extractResourceAttributes(resource, context);
      const environmentAttributes = this.extractEnvironmentAttributes(context);
      
      const attributes = {
        user: userAttributes,
        resource: resourceAttributes,
        environment: environmentAttributes,
        action: action
      };

      let rbacGranted = false;
      let abacDecision = this.settings.abacSettings.defaultDecision;
      const evaluatedPolicies = [];

      // Evaluate RBAC permissions (these are simpler - if they exist, they grant access)
      if (applicableRules.rbacPermissions.length > 0) {
        rbacGranted = true;
        this.logger.info(`✅ Step 3a - RBAC evaluation: GRANTED (${applicableRules.rbacPermissions.length} matching permissions)`);
      } else {
        this.logger.info(`❌ Step 3a - RBAC evaluation: DENIED (no matching permissions)`);
      }

      // Evaluate ABAC policies with attribute conditions
      if (applicableRules.abacPolicies.length > 0) {
        this.logger.info(`🔍 Step 3b - ABAC evaluation: checking ${applicableRules.abacPolicies.length} policies`);
        
        // Sort policies by priority
        const sortedPolicies = applicableRules.abacPolicies.sort((a, b) => (b.priority || 100) - (a.priority || 100));

        for (const policy of sortedPolicies) {
          const policyResult = await this.evaluateAbacCondition(policy.condition, attributes, { userId, resource, action, context });
          
          evaluatedPolicies.push({
            policyId: policy._id.toString(),
            name: policy.name,
            resource: policy.resource,
            action: policy.action,
            effect: policy.effect,
            matches: policyResult,
            priority: policy.priority || 100
          });

          // Apply combining algorithm
          if (policyResult) {
            this.logger.info(`📋 Policy "${policy.name}" matches - effect: ${policy.effect}`);
            
            if (this.settings.abacSettings.combiningAlgorithm === "deny-overrides" && policy.effect === "DENY") {
              abacDecision = "DENY";
              break;
            } else if (this.settings.abacSettings.combiningAlgorithm === "permit-overrides" && policy.effect === "ALLOW") {
              abacDecision = "ALLOW";
            } else if (this.settings.abacSettings.combiningAlgorithm === "first-applicable") {
              abacDecision = policy.effect;
              break;
            } else if (policy.effect === "ALLOW") {
              abacDecision = "ALLOW";
            }
          }
        }
      } else {
        this.logger.info(`⚪ Step 3b - ABAC evaluation: no applicable policies`);
      }

      // Final decision combining RBAC and ABAC
      const finalAuthorized = this.combineDecisions(rbacGranted, abacDecision === "ALLOW", context);

      this.logger.info(`🏁 Step 3 - Final decision: RBAC=${rbacGranted}, ABAC=${abacDecision}, Final=${finalAuthorized}`);

      return {
        authorized: finalAuthorized,
        rbacGranted,
        abacDecision,
        evaluatedPolicies,
        attributes,
        combiningAlgorithm: this.settings.abacSettings.combiningAlgorithm
      };

    } catch (error) {
      this.logger.error("Attribute-based evaluation error:", error);
      return {
        authorized: false,
        error: error.message
      };
    }
  }

  /**
   * Helper method to check if a policy might apply to given roles
   * This is a basic pre-filter to avoid evaluating complex conditions unnecessarily
   */
  async policyMightApplyToRoles(policy, userRoles) {
    try {
      // If policy condition doesn't reference userRole, it might apply
      const conditionStr = JSON.stringify(policy.condition);
      if (!conditionStr.includes('userRole')) {
        return true;
      }

      // Simple check: if policy mentions any of the user's roles, it might apply
      for (const role of userRoles) {
        if (conditionStr.includes(role)) {
          return true;
        }
      }

      // Check for role-based conditions more thoroughly
      return this.checkConditionForRoles(policy.condition, userRoles);
    } catch (error) {
      // If we can't determine, assume it might apply to be safe
      return true;
    }
  }

  /**
   * Recursively check if condition might apply to user roles
   */
  checkConditionForRoles(condition, userRoles) {
    if (!condition || typeof condition !== 'object') {
      return true;
    }

    // Check AND conditions
    if (condition.and) {
      return condition.and.some(subCondition => this.checkConditionForRoles(subCondition, userRoles));
    }

    // Check OR conditions  
    if (condition.or) {
      return condition.or.some(subCondition => this.checkConditionForRoles(subCondition, userRoles));
    }

    // Check userRole conditions
    if (condition.userRole) {
      if (condition.userRole.in) {
        return condition.userRole.in.some(role => userRoles.includes(role));
      }
      if (condition.userRole.notIn) {
        return !condition.userRole.notIn.every(role => userRoles.includes(role));
      }
    }

    // For other conditions, assume they might apply
    return true;
  }
}

module.exports = CloudAuthorizationService;