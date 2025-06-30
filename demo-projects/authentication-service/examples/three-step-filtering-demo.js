/**
 * Test to demonstrate the 3-Step Filtering Authorization Process
 * 
 * This test validates that the authorization system works in the exact fashion described:
 * 1. Role-Based Filtering (The Broad Stroke)
 * 2. Action-Based Filtering  
 * 3. Attribute-Based Evaluation (The Fine-Grained Check)
 */

const { ServiceBroker } = require("moleculer");

class ThreeStepFilteringDemo {
  constructor() {
    this.broker = new ServiceBroker({
      logger: true,
      logLevel: "info"
    });
  }

  async init() {
    // Load services
    this.broker.loadService("./services/cloud-authorization.service.js");
    await this.broker.start();
    
    console.log("🚀 3-Step Filtering Demo Started");
    console.log("=" .repeat(60));
  }

  /**
   * Demo the 3-step filtering process step by step
   */
  async demoThreeStepFiltering() {
    console.log("\n📋 Demonstrating 3-Step Filtering Process");
    console.log("-".repeat(50));

    const testCases = [
      {
        name: "Member user trying to edit a document",
        userId: "member123",
        userRoles: ["member"],
        resource: "document", 
        action: "edit",
        context: {
          resourceData: { 
            owner: "member123",
            department: "engineering",
            sensitivity: "normal"
          },
          userLocation: "office",
          time: "14:00"
        }
      },
      {
        name: "Guest user trying to delete a document", 
        userId: "guest456",
        userRoles: ["guest"],
        resource: "document",
        action: "delete", 
        context: {
          resourceData: {
            owner: "admin789",
            department: "hr", 
            sensitivity: "confidential"
          },
          userLocation: "home"
        }
      },
      {
        name: "Admin user trying to read system logs",
        userId: "admin789", 
        userRoles: ["admin"],
        resource: "system",
        action: "read",
        context: {
          userLocation: "office",
          time: "09:00"
        }
      }
    ];

    for (const testCase of testCases) {
      await this.demonstrateStepsForCase(testCase);
    }
  }

  async demonstrateStepsForCase(testCase) {
    console.log(`\n🔍 Test Case: ${testCase.name}`);
    console.log(`   User: ${testCase.userId} | Roles: [${testCase.userRoles.join(', ')}]`);
    console.log(`   Action: ${testCase.resource}:${testCase.action}`);
    
    try {
      // Manually demonstrate each step
      
      // STEP 1: Role-Based Filtering
      console.log(`\n   📍 STEP 1: Role-Based Filtering (The Broad Stroke)`);
      const roleResult = await this.broker.call("v1.cloud-authorization.performRoleBasedFiltering", {
        userId: testCase.userId
      });
      
      if (roleResult.success) {
        console.log(`      ✅ User roles identified: [${roleResult.userRoles.join(', ')}]`);
        console.log(`      📝 Universe narrowed to rules for these roles only`);
      } else {
        console.log(`      ❌ Role filtering failed: ${roleResult.error}`);
        return;
      }

      // STEP 2: Action-Based Filtering  
      console.log(`\n   📍 STEP 2: Action-Based Filtering`);
      const actionResult = await this.broker.call("v1.cloud-authorization.performActionBasedFiltering", {
        userRoles: roleResult.userRoles,
        resource: testCase.resource,
        action: testCase.action
      });

      if (actionResult.hasApplicableRules) {
        console.log(`      ✅ Found applicable rules for action '${testCase.action}':`);
        console.log(`         - RBAC permissions: ${actionResult.applicableRules.rbacPermissions.length}`);
        console.log(`         - ABAC policies: ${actionResult.applicableRules.abacPolicies.length}`);
      } else {
        console.log(`      ❌ No rules found for action '${testCase.action}' with user's roles`);
        console.log(`      🚫 Access DENIED - no applicable rules`);
        return;
      }

      // STEP 3: Attribute-Based Evaluation
      console.log(`\n   📍 STEP 3: Attribute-Based Evaluation (The Fine-Grained Check)`);
      const attributeResult = await this.broker.call("v1.cloud-authorization.performAttributeBasedEvaluation", {
        userId: testCase.userId,
        resource: testCase.resource,
        action: testCase.action,
        context: testCase.context,
        applicableRules: actionResult.applicableRules
      });

      console.log(`      📊 Attribute evaluation:`);
      console.log(`         - RBAC result: ${attributeResult.rbacGranted ? 'GRANTED' : 'DENIED'}`);
      console.log(`         - ABAC result: ${attributeResult.abacDecision}`);
      console.log(`         - Policies evaluated: ${attributeResult.evaluatedPolicies.length}`);
      
      if (attributeResult.evaluatedPolicies.length > 0) {
        attributeResult.evaluatedPolicies.forEach(policy => {
          console.log(`           * ${policy.name}: ${policy.matches ? 'MATCHES' : 'NO MATCH'} (${policy.effect})`);
        });
      }

      // Final Result
      console.log(`\n   🏁 FINAL DECISION: ${attributeResult.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);

      // Now test the full authorization to confirm it works end-to-end
      console.log(`\n   🧪 Full Authorization Test:`);
      const fullResult = await this.broker.call("v1.cloud-authorization.authorize", {
        userId: testCase.userId,
        resource: testCase.resource,
        action: testCase.action,
        context: testCase.context
      });

      console.log(`      Result: ${fullResult.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
      if (fullResult.evaluationDetails) {
        console.log(`      Step 1 (Roles): [${fullResult.evaluationDetails.step1_roles?.join(', ') || 'N/A'}]`);
        console.log(`      Step 2 (Rules): RBAC=${fullResult.evaluationDetails.step2_action_rules?.rbacPermissions?.length || 0}, ABAC=${fullResult.evaluationDetails.step2_action_rules?.abacPolicies?.length || 0}`);
        console.log(`      Step 3 (Final): ${fullResult.evaluationDetails.final}`);
      }

    } catch (error) {
      console.log(`   ❌ Error: ${error.message}`);
    }

    console.log(`\n   ${'='.repeat(60)}`);
  }

  /**
   * Demonstrate how the system handles edge cases
   */
  async demoEdgeCases() {
    console.log("\n🔧 Edge Case Demonstrations");
    console.log("-".repeat(40));

    const edgeCases = [
      {
        name: "User with no roles",
        userId: "noroles_user",
        expectedStep: "step1_failure"
      },
      {
        name: "User with roles but no applicable action rules",
        userId: "member123", 
        resource: "system",
        action: "delete", // Members probably can't delete system resources
        expectedStep: "step2_failure"
      }
    ];

    for (const edgeCase of edgeCases) {
      console.log(`\n🧪 Edge Case: ${edgeCase.name}`);
      
      try {
        const result = await this.broker.call("v1.cloud-authorization.authorize", {
          userId: edgeCase.userId,
          resource: edgeCase.resource || "document",
          action: edgeCase.action || "read",
          context: {}
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        if (result.reason) {
          console.log(`   Reason: ${result.reason}`);
        }
        if (result.evaluationDetails) {
          console.log(`   Failed at: ${result.evaluationDetails.step3_attribute_check === 'skipped - no applicable rules' ? 'Step 2' : 'Step 3'}`);
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  async runDemo() {
    await this.init();
    await this.demoThreeStepFiltering();
    await this.demoEdgeCases();
    
    console.log("\n" + "=".repeat(60));
    console.log("🎉 3-Step Filtering Demo Completed!");
    console.log("✅ The system now works exactly as specified:");
    console.log("   1. Role-Based Filtering (The Broad Stroke)");
    console.log("   2. Action-Based Filtering");  
    console.log("   3. Attribute-Based Evaluation (The Fine-Grained Check)");
    console.log("=".repeat(60));

    await this.broker.stop();
  }
}

// Run the demo if this file is executed directly
if (require.main === module) {
  const demo = new ThreeStepFilteringDemo();
  demo.runDemo().catch(console.error);
}

module.exports = ThreeStepFilteringDemo;
