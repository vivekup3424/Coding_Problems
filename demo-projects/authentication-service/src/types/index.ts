export interface User {
  id?: string;
  email: string;
  username: string;
  password: string;
  firstName: string;
  lastName: string;
  roles: string[];
  isActive?: boolean;
  lastLogin?: Date;
  createdAt?: Date;
  updatedAt?: Date;
  metadata?: Record<string, any>;
}

export interface RolePermission {
  id: string;
  role: string;
  resource: string;
  action: string;
  effect: 'allow' | 'deny';
  conditions?: Record<string, any>;
  description?: string;
  createdAt?: Date;
  updatedAt?: Date;
}

export interface LoginRequest {
  email: string;
  password: string;
}

export interface LoginResponse {
  success: boolean;
  token?: string;
  user?: Omit<User, 'password'>;
  message?: string;
}

export interface AuthorizationRequest {
  userId: string;
  resource: string;
  action: string;
  context?: Record<string, any>;
}

export interface AuthorizationResponse {
  allowed: boolean;
  reason?: string;
  matchedPermissions?: RolePermission[];
  appliedRules?: string[];
}

// Database connection interface
export interface DatabaseConfig {
  uri: string;
  dbName: string;
}

// JWT payload interface
export interface JWTPayload {
  userId: string;
  email: string;
  roles: string[];
  iat?: number;
  exp?: number;
}

// API Response wrapper
export interface ApiResponse<T = any> {
  success: boolean;
  data?: T;
  message?: string;
  error?: string;
}

interface Policy{
    id: string,
    name: string;
    effect: "Allow" | "Deny";
    principals: string[];
    resources: string[],
    actions: string[],
    conditions?:
}