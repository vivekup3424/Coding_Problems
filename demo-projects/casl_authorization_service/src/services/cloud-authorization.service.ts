import { Service, ServiceBroker, Context } from 'moleculer';
import { readFileSync } from 'fs';
import { join } from 'path';
import { config } from '../config';
import { Permission } from "../types"
import { createMongoAbility } from '@casl/ability';

/**
 * Cloud Authorization Service  
 * Handles permission checking for cloud-based operations
 */
export default class CloudAuthorizationService extends Service {
  private permissions?: Record<string, Permission[]>;
  private userRoles?: Record<string, string[]>;

  public constructor(broker: ServiceBroker) {
    super(broker);
    this.parseServiceSchema({
      name: config.services.cloudAuthorization.name,
      version: config.services.cloudAuthorization.version,
      
      actions: {
        can: {
          params: {
            userId: 'string',
            action: 'string', 
            subject: 'string',
            resource: { type: 'object', optional: true }
          },
          handler: this.can
        },
        
        getUserPermissions: {
          params: {
            userId: 'string'
          },
          handler: this.getUserPermissions
        },
        
        getUserRoles: {
          params: {
            userId: 'string'
          },
          handler: this.getUserRoles
        }
      },
      
      started: this.serviceStarted
    });
  }

  /**
   * Service started lifecycle event handler
   */
  async serviceStarted(): Promise<void> {
    try {
      const permissionsPath = join(process.cwd(), config.dataFiles.cloudPermissions);
      const permissionsData = readFileSync(permissionsPath, 'utf8');
      this.permissions = JSON.parse(permissionsData);
      
      // Load user roles mapping
      const userRolesPath = join(process.cwd(), './data/user-roles.json');
      const userRolesData = readFileSync(userRolesPath, 'utf8');
      this.userRoles = JSON.parse(userRolesData);
      
      this.logger.info(`✅ Loaded cloud permissions from ${permissionsPath}`);
      this.logger.info(`✅ Loaded user roles mapping`);
    } catch (error) {
      this.logger.error('❌ Failed to load cloud permissions:', error);
      throw error;
    }
  }

  /**
   * Get all permissions for a user including role-based permissions
   */
  private getAllUserPermissions(userId: string): Permission[] {
    if (!this.permissions || !this.userRoles) {
      return [];
    }

    const allPermissions: Permission[] = [];
    
    // Get user roles
    const roles = this.userRoles[userId] || [];
    
    // Collect permissions from all roles
    roles.forEach(role => {
      const rolePermissions = this.permissions![role] || [];
      allPermissions.push(...rolePermissions);
    });

    return allPermissions;
  }

  /**
   * Check if user can perform action on subject
   */
  async can(ctx: Context<{ 
    userId: string; 
    action: string; 
    subject: string; 
    resource?: any 
  }>): Promise<{ allowed: boolean; reason?: string }> {
    const { userId, action, subject, resource } = ctx.params;
    
    this.logger.info(`🔍 Checking cloud permission: ${userId} can ${action} ${subject}`);
    
    if (!this.permissions || !this.userRoles) {
      return { allowed: false, reason: 'Permissions not loaded' };
    }

    // Get all user permissions (from all their roles)
    const userPermissions = this.getAllUserPermissions(userId);
    
    if (userPermissions.length === 0) {
      return { allowed: false, reason: 'User has no cloud permissions' };
    }

    // Create ability from user permissions
    const userAbility = createMongoAbility(userPermissions as any);
    
    // Check if user can perform the action
    const hasPermission = userAbility.can(action, subject, resource);
    
    return { allowed: hasPermission };
  }

  /**
   * Get all permissions for a user
   */
  async getUserPermissions(ctx: Context<{ userId: string }>): Promise<Permission[]> {
    const { userId } = ctx.params;
    
    if (!this.permissions) {
      return [];
    }
    
    // Use the helper method to get all user permissions including role-based ones
    return this.getAllUserPermissions(userId);
  }

  /**
   * Get user roles for cloud operations
   */
  async getUserRoles(ctx: Context<{ userId: string }>): Promise<string[]> {
    const { userId } = ctx.params;
    
    if (!this.userRoles) {
      return [];
    }
    
    return this.userRoles[userId] || [];
  }
}
