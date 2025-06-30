# RBAC + ABAC Authorization System

This enhanced authentication service combines **Role-Based Access Control (RBAC)** with **Attribute-Based Access Control (ABAC)** to provide fine-grained, context-aware authorization for home automation systems.

## Overview

### RBAC (Role-Based Access Control)
- **Traditional approach** based on user roles and permissions
- Users are assigned roles (admin, homeowner, user, guest)
- Roles have associated permissions (device:read, device:write, etc.)
- Simple and efficient for basic authorization

### ABAC (Attribute-Based Access Control)
- **Context-aware approach** based on multiple attributes
- Considers user attributes, resource attributes, environment attributes
- Supports complex conditions and rules
- More flexible and granular than RBAC alone

## Architecture

```
┌─────────────────┐    ┌─────────────────┐
│ Cloud           │    │ Local           │
│ Authorization   │    │ Authorization   │
│ Service         │    │ Service         │
│                 │    │                 │
│ • RBAC + ABAC   │◄──►│ • Local RBAC    │
│ • Policy Mgmt   │    │ • Local ABAC    │
│ • Database      │    │ • Cache         │
│ • Full Features │    │ • Offline Mode  │
└─────────────────┘    └─────────────────┘
```

## Features

### Cloud Authorization Service

#### RBAC Features
- Role and permission management
- User role assignment
- Hierarchical permission checking
- Wildcard permissions support

#### ABAC Features
- **Policy-based authorization**
- **Multiple attribute types**:
  - User attributes (roles, location, department)
  - Resource attributes (type, owner, sensitivity)
  - Environment attributes (time, date, IP address)
- **Flexible condition operators**:
  - `equals`, `in`, `notIn`, `before`, `after`, `contains`
  - Logical operators: `and`, `or`, `not`
- **Policy combining algorithms**:
  - `deny-overrides` (default)
  - `permit-overrides`
  - `first-applicable`

### Local Authorization Service

#### Local RBAC Features
- Cached permissions for offline operation
- Emergency authorization codes
- Local-only permissions
- Fallback to cloud when available

#### Local ABAC Features
- **Local policy evaluation** for offline scenarios
- **Emergency override policies**
- **Device ownership policies**
- **Time-based restrictions** for offline mode

## ABAC Policy Structure

Each ABAC policy has the following structure:

```javascript
{
  id: "unique-policy-id",
  name: "Human Readable Policy Name",
  description: "Policy description",
  resource: "device|room|automation|security|*",
  action: "read|write|admin|execute|*", 
  effect: "ALLOW|DENY",
  priority: 100, // Higher number = higher priority
  condition: {
    // Complex condition logic
  }
}
```

## Example Scenarios

### 1. Time-Based Access Control

**Scenario**: Regular users cannot control devices between 23:00 and 06:00

```javascript
{
  id: "time-based-access",
  name: "Time-based Access Control", 
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
}
```

**Test Cases**:
- ❌ Regular user at 02:00 → DENIED
- ✅ Homeowner at 02:00 → ALLOWED  
- ✅ Regular user at 14:00 → ALLOWED

### 2. Location-Based Security Access

**Scenario**: Security admin functions only allowed from trusted locations

```javascript
{
  id: "location-based-access",
  name: "Location-based Access Control",
  resource: "security", 
  action: "admin",
  effect: "DENY",
  priority: 200,
  condition: {
    userLocation: { notIn: ["home", "trusted"] }
  }
}
```

**Test Cases**:
- ✅ Admin from home → ALLOWED
- ❌ Admin from public WiFi → DENIED
- ✅ Admin from trusted office → ALLOWED

### 3. Device Ownership Control

**Scenario**: Users can only control devices they own

```javascript
{
  id: "device-ownership",
  name: "Device Ownership Control",
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
}
```

**Test Cases**:
- ✅ User controlling own device → ALLOWED
- ❌ User controlling other's device → DENIED  
- ✅ Homeowner controlling any device → ALLOWED (via RBAC)

### 4. Emergency Override

**Scenario**: Emergency actions bypass all restrictions

```javascript
{
  id: "emergency-override",
  name: "Emergency Override Policy", 
  resource: "*",
  action: "*",
  effect: "ALLOW", 
  priority: 1000, // Highest priority
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
}
```

**Test Cases**:
- ✅ Emergency stop at night → ALLOWED
- ✅ Alarm disable in emergency → ALLOWED
- ✅ Any action with emergencyMode=true → ALLOWED

### 5. Business Hours Automation

**Scenario**: Non-admin users can only run automations during business hours

```javascript
{
  id: "business-hours-automation",
  name: "Business Hours Automation",
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
}
```

**Test Cases**:
- ❌ Regular user on weekend → DENIED
- ✅ Regular user during business hours → ALLOWED
- ✅ Admin anytime → ALLOWED

### 6. Offline Mode Restrictions

**Scenario**: Restrict non-emergency actions during offline mode

```javascript
{
  id: "offline-time-restriction", 
  name: "Offline Time Restriction",
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
```

## API Reference

### Cloud Authorization Service

#### `authorize(userId, resource, action, context)`
Enhanced authorization with RBAC + ABAC evaluation

#### `createAbacPolicy(name, description, resource, action, effect, condition, priority)`
Create a new ABAC policy

#### `updateAbacPolicy(policyId, updates)`
Update an existing ABAC policy

#### `deleteAbacPolicy(policyId)`
Delete an ABAC policy

#### `listAbacPolicies()`
List all ABAC policies

#### `evaluateAbacPolicies(userId, resource, action, context)`
Evaluate ABAC policies for a request

### Local Authorization Service

#### `authorize(userId, resource, action, context)`
Local authorization with fallback and local ABAC

#### `evaluateLocalAbacPolicies(userId, resource, action, context)` 
Evaluate local ABAC policies

#### `setOfflineMode(enabled)`
Enable/disable offline mode

#### `emergencyAuthorize(userId, action, authCode)`
Emergency authorization with optional code

## Configuration

### Cloud ABAC Settings

```javascript
abacSettings: {
  enabled: true,
  defaultDecision: "DENY", 
  policyEvaluationOrder: "priority",
  combiningAlgorithm: "deny-overrides"
}
```

### Local ABAC Settings

```javascript
localAbacSettings: {
  enabled: true,
  defaultDecision: "DENY",
  combiningAlgorithm: "deny-overrides"  
}
```

## Running Examples

### Demo Script
```bash
node examples/rbac-abac-demo.js
```

### Tests
```bash
npm test -- test/rbac-abac.test.js
```

## Benefits of RBAC + ABAC

1. **Flexibility**: ABAC provides fine-grained control while RBAC offers simplicity
2. **Context Awareness**: Decisions based on time, location, device ownership, etc.
3. **Security**: Multiple layers of authorization checks
4. **Offline Support**: Local policies for when cloud is unavailable
5. **Emergency Handling**: Override mechanisms for critical situations
6. **Scalability**: Policy-based approach scales better than hardcoded rules

## Best Practices

1. **Use RBAC for basic permissions**, ABAC for complex scenarios
2. **Set appropriate policy priorities** to ensure correct evaluation order
3. **Test emergency override policies** thoroughly
4. **Monitor policy performance** for complex conditions
5. **Keep local policies simple** for offline reliability
6. **Use deny-overrides** combining algorithm for security
7. **Regular policy audits** to remove unused or conflicting policies

## Security Considerations

1. **Policy conflicts**: Ensure policies don't contradict each other
2. **Performance impact**: Complex conditions can slow authorization
3. **Emergency access**: Always provide emergency override mechanisms
4. **Audit logging**: Log all authorization decisions for security analysis
5. **Cache security**: Protect cached permissions in local storage
6. **Attribute validation**: Validate all attributes before evaluation
