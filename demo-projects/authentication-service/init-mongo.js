// MongoDB initialization script
db = db.getSiblingDB('home_automation_auth');

// Create collections with indexes
db.createCollection('users');
db.createCollection('roles');
db.createCollection('permissions');

// Create indexes for better performance
db.users.createIndex({ email: 1 }, { unique: true });
db.users.createIndex({ username: 1 }, { unique: true });
db.roles.createIndex({ name: 1 }, { unique: true });
db.permissions.createIndex({ name: 1 }, { unique: true });
db.permissions.createIndex({ resource: 1, action: 1 });

print('Database initialized successfully!');
