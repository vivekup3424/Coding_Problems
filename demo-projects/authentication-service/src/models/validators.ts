import { User, Permission, Role, LoginRequest, AuthorizationRequest, PermissionAssignment, RoleAssignment } from '../types';

export class UserValidator {
  static validate(data: Partial<User>): User {
    if (!data.email || !this.isValidEmail(data.email)) {
      throw new Error('Valid email is required');
    }
    if (!data.username || data.username.length < 3 || data.username.length > 30) {
      throw new Error('Username must be 3-30 characters');
    }
    if (!data.password || data.password.length < 8) {
      throw new Error('Password must be at least 8 characters');
    }
    if (!data.firstName || data.firstName.length < 2 || data.firstName.length > 50) {
      throw new Error('First name must be 2-50 characters');
    }
    if (!data.lastName || data.lastName.length < 2 || data.lastName.length > 50) {
      throw new Error('Last name must be 2-50 characters');
    }

    return {
      id: data.id,
      email: data.email,
      username: data.username,
      password: data.password,
      firstName: data.firstName,
      lastName: data.lastName,
      roles: data.roles || [],
      isActive: data.isActive !== undefined ? data.isActive : true,
      lastLogin: data.lastLogin,
      createdAt: data.createdAt || new Date(),
      updatedAt: data.updatedAt || new Date(),
      metadata: data.metadata
    };
  }

  private static isValidEmail(email: string): boolean {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
  }
}

export class PermissionValidator {
  static validate(data: Partial<Permission>): Permission {
    if (!data.name) {
      throw new Error('Permission name is required');
    }
    if (!data.resource) {
      throw new Error('Resource is required');
    }
    if (!data.action) {
      throw new Error('Action is required');
    }

    return {
      id: data.id,
      name: data.name,
      resource: data.resource,
      action: data.action,
      conditions: data.conditions,
      description: data.description,
      createdAt: data.createdAt || new Date(),
      updatedAt: data.updatedAt || new Date()
    };
  }
}

export class RoleValidator {
  static validate(data: Partial<Role>): Role {
    if (!data.name) {
      throw new Error('Role name is required');
    }

    return {
      id: data.id,
      name: data.name,
      description: data.description,
      permissions: data.permissions || [],
      isSystemRole: data.isSystemRole || false,
      createdAt: data.createdAt || new Date(),
      updatedAt: data.updatedAt || new Date()
    };
  }
}

export class LoginValidator {
  static validate(data: any): LoginRequest {
    if (!data.email || !UserValidator['isValidEmail'](data.email)) {
      throw new Error('Valid email is required');
    }
    if (!data.password) {
      throw new Error('Password is required');
    }

    return {
      email: data.email,
      password: data.password
    };
  }
}

export class AuthorizationValidator {
  static validate(data: any): AuthorizationRequest {
    if (!data.userId) {
      throw new Error('User ID is required');
    }
    if (!data.resource) {
      throw new Error('Resource is required');
    }
    if (!data.action) {
      throw new Error('Action is required');
    }

    return {
      userId: data.userId,
      resource: data.resource,
      action: data.action,
      context: data.context
    };
  }
}
