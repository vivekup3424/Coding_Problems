const Joi = require("joi");

// User model schema
const userSchema = Joi.object({
  id: Joi.string().optional(),
  email: Joi.string().email().required(),
  username: Joi.string().alphanum().min(3).max(30).required(),
  password: Joi.string().min(8).required(),
  firstName: Joi.string().min(2).max(50).required(),
  lastName: Joi.string().min(2).max(50).required(),
  roles: Joi.array().items(Joi.string()).default([]),
  isActive: Joi.boolean().default(true),
  lastLogin: Joi.date().optional(),
  createdAt: Joi.date().default(Date.now),
  updatedAt: Joi.date().default(Date.now),
  metadata: Joi.object().optional()
});

// Login request schema
const loginSchema = Joi.object({
  email: Joi.string().email().required(),
  password: Joi.string().required()
});

// role-permission model schema
const rolePermissionSchema = Joi.object({
  id: Joi.string().optional(),
  role: Joi.string().required(),
  permission: Joi.string().required(), // e.g., "device", "room", "system"
  action: Joi.string().required(),   // e.g., "read", "write", "execute", "admin"
  conditions: Joi.object().optional(), // Additional conditions for the permission
  description: Joi.string().optional(),
  createdAt: Joi.date().default(Date.now),
  updatedAt: Joi.date().default(Date.now)
});

// Role model schema
const roleSchema = Joi.object({
  id: Joi.string().optional(),
  name: Joi.string().required(),
  description: Joi.string().optional(),
  permissions: Joi.array().items(Joi.string()).default([]), // Array of permission IDs
  isSystemRole: Joi.boolean().default(false), // Whether this is a built-in system role
  createdAt: Joi.date().default(Date.now),
  updatedAt: Joi.date().default(Date.now)
});

// Authorization request schema
const authorizationRequestSchema = Joi.object({
  userId: Joi.string().required(),
  resource: Joi.string().required(),
  action: Joi.string().required(),
  context: Joi.object().optional() // Additional context for authorization
});

// Permission assignment schema
const permissionAssignmentSchema = Joi.object({
  roleId: Joi.string().required(),
  permissionIds: Joi.array().items(Joi.string()).required()
});

// Role assignment schema
const roleAssignmentSchema = Joi.object({
  userId: Joi.string().required(),
  roleIds: Joi.array().items(Joi.string()).required()
});

module.exports = {
  permissionSchema,
  roleSchema,
  authorizationRequestSchema,
  permissionAssignmentSchema,
  roleAssignmentSchema
};


module.exports = {
  userSchema,
  loginSchema,
  updateUserSchema,
  changePasswordSchema
};
