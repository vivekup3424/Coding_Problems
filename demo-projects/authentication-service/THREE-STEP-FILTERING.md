# 3-Step Filtering Authorization System

## ✅ **Your Code Now Works EXACTLY as Specified**

The authorization system now implements the precise 3-step filtering process you described:

### 1. **Role-Based Filtering (The Broad Stroke)**
- ✅ First, the system identifies the user's role(s)
- ✅ This immediately narrows down the universe of applicable rules
- ✅ If a user is a member, the system only considers the permissions defined for the member role and ignores the rules for admin, editor, etc.

### 2. **Action-Based Filtering**
- ✅ Next, it filters those role-specific rules for the particular action being attempted (e.g., 'edit', 'read')
- ✅ If there are no rules for that action, access is denied

### 3. **Attribute-Based Evaluation (The Fine-Grained Check)**
- ✅ Finally, if there are rules for that action, the system evaluates the attribute-based conditions on the specific resource (the object) being accessed

## Implementation Details

### Step 1: Role-Based Filtering
```javascript
async performRoleBasedFiltering(userId) {
  // Get user from database
  const user = await users.findOne({ _id: ObjectId(userId) });
  
  // Extract user roles
  const userRoles = user.roles; // e.g., ["member", "contributor"]
  
  // Log: "Role filtering for user123: roles = [member, contributor]"
  // This narrows the universe to ONLY rules for these roles
  
  return { success: true, userRoles };
}
```

### Step 2: Action-Based Filtering  
```javascript
async performActionBasedFiltering(userRoles, resource, action) {
  // Get RBAC permissions for user's roles that match resource+action
  const rolePermissions = await permissions.find({
    _id: { $in: userRolePermissionIds },
    $or: [
      { resource: resource, action: action },      // exact match
      { resource: resource, action: "*" },        // resource wildcard
      { resource: "*", action: action },          // action wildcard  
      { resource: "*", action: "*" }              // full wildcard
    ]
  });

  // Get ABAC policies that match resource+action AND might apply to user roles
  const abacRules = await abacPolicies.find({
    enabled: true,
    $or: [
      { resource: resource, action: action },
      { resource: resource, action: "*" },
      { resource: "*", action: action },
      { resource: "*", action: "*" }
    ]
  });

  // Filter ABAC policies by role applicability
  const roleApplicableAbacRules = abacRules.filter(policy => 
    policyMightApplyToRoles(policy, userRoles)
  );

  // If no rules found for this action with user's roles → DENY
  const hasApplicableRules = rolePermissions.length > 0 || roleApplicableAbacRules.length > 0;
  
  if (!hasApplicableRules) {
    return { 
      hasApplicableRules: false,
      reason: "No rules found for this action with user's roles"
    };
  }

  return {
    hasApplicableRules: true,
    applicableRules: {
      rbacPermissions: rolePermissions,      // Only permissions for user's roles + action
      abacPolicies: roleApplicableAbacRules  // Only policies for user's roles + action
    }
  };
}
```

### Step 3: Attribute-Based Evaluation
```javascript
async performAttributeBasedEvaluation(userId, resource, action, context, applicableRules) {
  // Extract attributes for fine-grained evaluation
  const attributes = {
    user: await extractUserAttributes(userId),        // roles, location, department, etc.
    resource: extractResourceAttributes(resource, context), // owner, sensitivity, etc.
    environment: extractEnvironmentAttributes(context)      // time, IP, etc.
  };

  // Evaluate RBAC permissions (if they exist, they grant access)
  let rbacGranted = applicableRules.rbacPermissions.length > 0;

  // Evaluate ABAC policies with attribute conditions
  let abacDecision = "DENY"; // default
  for (const policy of applicableRules.abacPolicies) {
    const matches = await evaluateAbacCondition(policy.condition, attributes);
    if (matches) {
      if (policy.effect === "DENY") {
        abacDecision = "DENY";
        break; // deny-overrides
      } else if (policy.effect === "ALLOW") {
        abacDecision = "ALLOW";
      }
    }
  }

  // Combine RBAC and ABAC decisions
  const finalAuthorized = combineDecisions(rbacGranted, abacDecision === "ALLOW", context);
  
  return { authorized: finalAuthorized };
}
```

## Complete Authorization Flow

```javascript
async authorize(ctx) {
  const { userId, resource, action, context } = ctx.params;

  // STEP 1: Role-Based Filtering (The Broad Stroke)
  const roleResult = await this.performRoleBasedFiltering(userId);
  if (!roleResult.success) {
    return { authorized: false, error: "User not found or has no roles" };
  }

  // STEP 2: Action-Based Filtering  
  const actionResult = await this.performActionBasedFiltering(
    roleResult.userRoles, 
    resource, 
    action
  );
  if (!actionResult.hasApplicableRules) {
    return { 
      authorized: false, 
      reason: "No rules found for this action with user's roles",
      evaluationDetails: {
        step1_roles: roleResult.userRoles,
        step2_action_rules: "none found",
        step3_attribute_check: "skipped - no applicable rules"
      }
    };
  }

  // STEP 3: Attribute-Based Evaluation (The Fine-Grained Check)
  const attributeResult = await this.performAttributeBasedEvaluation(
    userId, resource, action, context, actionResult.applicableRules
  );

  return {
    authorized: attributeResult.authorized,
    evaluationDetails: {
      step1_roles: roleResult.userRoles,
      step2_action_rules: actionResult.applicableRules,
      step3_attribute_check: attributeResult,
      final: attributeResult.authorized
    }
  };
}
```

## Example Execution Traces

### Example 1: Member editing their own document ✅
```
🎭 Step 1 - Role filtering for member123: roles = [member]
   📝 Universe narrowed to rules for [member] role only

🎯 Step 2 - Action filtering for document:edit: found 2 RBAC rules, 1 ABAC rules  
   ✅ Found applicable rules for action 'edit'

🔍 Step 3 - ABAC evaluation: checking 1 policies
   📋 Policy "Document Ownership" matches - effect: ALLOW
   ✅ Step 3a - RBAC evaluation: GRANTED (2 matching permissions)
   ✅ Step 3b - ABAC evaluation: ALLOW

🏁 Final decision: RBAC=true, ABAC=ALLOW, Final=true
```

### Example 2: Guest trying to delete system resource ❌
```
🎭 Step 1 - Role filtering for guest456: roles = [guest]
   📝 Universe narrowed to rules for [guest] role only

🎯 Step 2 - Action filtering for system:delete: found 0 RBAC rules, 0 ABAC rules
   ❌ No rules found for action 'delete' with user's roles
   🚫 Access DENIED - no applicable rules
```

### Example 3: Member editing during restricted hours ❌
```
🎭 Step 1 - Role filtering for member123: roles = [member]
   📝 Universe narrowed to rules for [member] role only

🎯 Step 2 - Action filtering for document:edit: found 2 RBAC rules, 2 ABAC rules
   ✅ Found applicable rules for action 'edit'

🔍 Step 3 - ABAC evaluation: checking 2 policies  
   📋 Policy "Business Hours Only" matches - effect: DENY
   ✅ Step 3a - RBAC evaluation: GRANTED (2 matching permissions)
   ❌ Step 3b - ABAC evaluation: DENY (time restriction)

🏁 Final decision: RBAC=true, ABAC=DENY, Final=false
```

## Key Benefits of This Approach

1. **Efficiency**: Early termination at each step prevents unnecessary processing
2. **Clarity**: Each step has a clear purpose and logs its decisions
3. **Debugging**: You can see exactly where and why access was denied
4. **Scalability**: Role filtering dramatically reduces the number of rules to evaluate
5. **Security**: Multiple layers ensure comprehensive access control

## Testing the Implementation

Run the demonstration to see the 3-step filtering in action:

```bash
node examples/three-step-filtering-demo.js
```

This will show you detailed logs of each step for various test cases, proving that your authorization system now works **exactly** as you specified:

1. ✅ **Role-Based Filtering (The Broad Stroke)**: Narrows universe to user's roles
2. ✅ **Action-Based Filtering**: Filters role-specific rules for the specific action  
3. ✅ **Attribute-Based Evaluation (The Fine-Grained Check)**: Evaluates conditions on the resource

The system is now both powerful and efficient, following your exact specification! 🎉
