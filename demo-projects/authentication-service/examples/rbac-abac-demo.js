/**
 * RBAC + ABAC Authorization Demo
 * 
 * This file demonstrates how the enhanced authorization system works
 * with both Role-Based Access Control (RBAC) and Attribute-Based Access Control (ABAC)
 * 
 * Scenarios covered:
 * 1. Time-based access control
 * 2. Location-based restrictions
 * 3. Device ownership control
 * 4. Emergency override scenarios
 * 5. Business hours automation
 * 6. Offline mode operations
 */

const { ServiceBroker } = require("moleculer");

class RbacAbacDemo {
  constructor() {
    this.broker = new ServiceBroker({
      logger: true,
      logLevel: "info"
    });
  }

  async init() {
    // Load services
    this.broker.loadService("./services/cloud-authorization.service.js");
    this.broker.loadService("./services/local-authorization.service.js");
    
    await this.broker.start();
    
    console.log("🚀 RBAC + ABAC Demo started");
    console.log("=" .repeat(60));
  }

  /**
   * Demo Scenario 1: Time-based Access Control
   * 
   * Regular users cannot control devices between 23:00 and 06:00
   * But admins and homeowners can access anytime
   */
  async demoTimeBasedAccess() {
    console.log("\n📅 Demo 1: Time-based Access Control");
    console.log("-".repeat(40));

    const scenarios = [
      {
        description: "Regular user trying to control device at night (23:30)",
        userId: "user123",
        resource: "device",
        action: "write",
        userRole: "user",
        context: {
          resourceData: { owner: "homeowner456" },
          // Simulate night time
          time: "23:30"
        }
      },
      {
        description: "Homeowner controlling device at night (23:30)",
        userId: "homeowner456", 
        resource: "device",
        action: "write",
        userRole: "homeowner",
        context: {
          resourceData: { owner: "homeowner456" },
          time: "23:30"
        }
      },
      {
        description: "Regular user controlling device during day (14:00)",
        userId: "user123",
        resource: "device", 
        action: "write",
        userRole: "user",
        context: {
          resourceData: { owner: "user123" },
          time: "14:00"
        }
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const result = await this.broker.call("v1.cloud-authorization.authorize", {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        if (result.evaluationDetails) {
          console.log(`   RBAC: ${result.evaluationDetails.rbac}`);
          console.log(`   ABAC: ${result.evaluationDetails.abac.decision}`);
          console.log(`   Policies applied: ${result.evaluationDetails.abac.policies?.length || 0}`);
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  /**
   * Demo Scenario 2: Location-based Security Access
   * 
   * Security admin functions only allowed from trusted locations
   */
  async demoLocationBasedAccess() {
    console.log("\n🌍 Demo 2: Location-based Access Control");
    console.log("-".repeat(40));

    const scenarios = [
      {
        description: "Admin accessing security from home",
        userId: "admin789",
        resource: "security",
        action: "admin",
        context: {
          userLocation: "home"
        }
      },
      {
        description: "Admin accessing security from public WiFi",
        userId: "admin789",
        resource: "security", 
        action: "admin",
        context: {
          userLocation: "public"
        }
      },
      {
        description: "Admin accessing security from trusted office",
        userId: "admin789",
        resource: "security",
        action: "admin", 
        context: {
          userLocation: "trusted"
        }
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const result = await this.broker.call("v1.cloud-authorization.authorize", {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        if (result.evaluationDetails?.abac?.policies) {
          const deniedPolicies = result.evaluationDetails.abac.policies.filter(p => p.matches && p.effect === 'DENY');
          if (deniedPolicies.length > 0) {
            console.log(`   Denied by policy: ${deniedPolicies[0].name}`);
          }
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  /**
   * Demo Scenario 3: Device Ownership Control
   * 
   * Users can only control devices they own (unless they're admin/homeowner)
   */
  async demoDeviceOwnership() {
    console.log("\n🏠 Demo 3: Device Ownership Control");
    console.log("-".repeat(40));

    const scenarios = [
      {
        description: "User controlling their own device",
        userId: "user123",
        resource: "device",
        action: "write",
        context: {
          resourceData: { owner: "user123" }
        }
      },
      {
        description: "User trying to control someone else's device", 
        userId: "user123",
        resource: "device",
        action: "write",
        context: {
          resourceData: { owner: "user456" }
        }
      },
      {
        description: "Homeowner controlling any device",
        userId: "homeowner789", 
        resource: "device",
        action: "write",
        context: {
          resourceData: { owner: "user123" }
        }
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const result = await this.broker.call("v1.cloud-authorization.authorize", {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        if (result.evaluationDetails?.abac?.policies) {
          const allowPolicies = result.evaluationDetails.abac.policies.filter(p => p.matches && p.effect === 'ALLOW');
          if (allowPolicies.length > 0) {
            console.log(`   Allowed by policy: ${allowPolicies[0].name}`);
          }
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  /**
   * Demo Scenario 4: Emergency Override
   * 
   * Emergency actions should bypass normal restrictions
   */
  async demoEmergencyOverride() {
    console.log("\n🚨 Demo 4: Emergency Override");
    console.log("-".repeat(40));

    const scenarios = [
      {
        description: "Emergency stop during restricted hours",
        userId: "user123",
        resource: "device",
        action: "emergency-stop",
        context: {
          time: "02:00", // Restricted time
          emergencyMode: true
        }
      },
      {
        description: "Regular user disabling alarm in emergency",
        userId: "user123", 
        resource: "security",
        action: "alarm-disable",
        context: {
          emergencyMode: true,
          userLocation: "public" // Normally restricted location
        }
      },
      {
        description: "Local emergency authorization (offline)",
        userId: "user123",
        resource: "device", 
        action: "emergency-stop",
        isLocal: true
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const service = scenario.isLocal ? "v1.local-authorization" : "v1.cloud-authorization";
        const result = await this.broker.call(`${service}.authorize`, {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        console.log(`   Source: ${result.source || 'cloud'}`);
        if (result.evaluationDetails?.abac?.policies) {
          const emergencyPolicies = result.evaluationDetails.abac.policies.filter(p => 
            p.matches && p.name.toLowerCase().includes('emergency')
          );
          if (emergencyPolicies.length > 0) {
            console.log(`   Emergency policy applied: ${emergencyPolicies[0].name}`);
          }
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  /**
   * Demo Scenario 5: Business Hours Automation
   * 
   * Non-admin users can only run automations during business hours
   */
  async demoBusinessHoursAutomation() {
    console.log("\n💼 Demo 5: Business Hours Automation");
    console.log("-".repeat(40));

    const scenarios = [
      {
        description: "Regular user running automation during weekend",
        userId: "user123",
        resource: "automation",
        action: "execute",
        context: {
          dayOfWeek: "saturday"
        }
      },
      {
        description: "Regular user running automation during business hours",
        userId: "user123",
        resource: "automation", 
        action: "execute",
        context: {
          dayOfWeek: "monday",
          time: "14:00"
        }
      },
      {
        description: "Admin running automation anytime",
        userId: "admin789",
        resource: "automation",
        action: "execute", 
        context: {
          dayOfWeek: "sunday",
          time: "22:00"
        }
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const result = await this.broker.call("v1.cloud-authorization.authorize", {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        if (result.evaluationDetails?.abac?.policies) {
          const businessHoursPolicies = result.evaluationDetails.abac.policies.filter(p => 
            p.matches && p.name.toLowerCase().includes('business')
          );
          if (businessHoursPolicies.length > 0) {
            console.log(`   Business hours policy: ${businessHoursPolicies[0].name}`);
          }
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }
  }

  /**
   * Demo Scenario 6: Offline Mode Operations
   * 
   * Local authorization with cached permissions and local ABAC policies
   */
  async demoOfflineMode() {
    console.log("\n🔌 Demo 6: Offline Mode Operations");
    console.log("-".repeat(40));

    // Simulate offline mode
    await this.broker.call("v1.local-authorization.setOfflineMode", { enabled: true });

    const scenarios = [
      {
        description: "Device control in offline mode during day",
        userId: "user123",
        resource: "device",
        action: "write",
        context: {
          resourceData: { owner: "user123" },
          time: "14:00"
        }
      },
      {
        description: "Device control in offline mode at night (restricted)",
        userId: "user123",
        resource: "device",
        action: "write", 
        context: {
          resourceData: { owner: "user123" },
          time: "02:00"
        }
      },
      {
        description: "Emergency action in offline mode",
        userId: "user123",
        resource: "device",
        action: "emergency-stop",
        context: {
          emergencyMode: true
        }
      }
    ];

    for (const scenario of scenarios) {
      console.log(`\n🔍 ${scenario.description}`);
      
      try {
        const result = await this.broker.call("v1.local-authorization.authorize", {
          userId: scenario.userId,
          resource: scenario.resource,
          action: scenario.action,
          context: scenario.context
        });

        console.log(`   Result: ${result.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);
        console.log(`   Source: ${result.source}`);
        if (result.warning) {
          console.log(`   ⚠️  ${result.warning}`);
        }
        if (result.evaluationDetails?.abac?.policies) {
          console.log(`   Local ABAC policies evaluated: ${result.evaluationDetails.abac.policies.length}`);
        }
      } catch (error) {
        console.log(`   Error: ${error.message}`);
      }
    }

    // Reset offline mode
    await this.broker.call("v1.local-authorization.setOfflineMode", { enabled: false });
  }

  /**
   * Demo Scenario 7: ABAC Policy Management
   * 
   * Creating, updating, and managing ABAC policies
   */
  async demoPolicyManagement() {
    console.log("\n⚙️ Demo 7: ABAC Policy Management");
    console.log("-".repeat(40));

    try {
      // List existing policies
      console.log("\n📋 Listing existing ABAC policies:");
      const policies = await this.broker.call("v1.cloud-authorization.listAbacPolicies");
      policies.policies.forEach(policy => {
        console.log(`   - ${policy.name} (${policy.resource}:${policy.action}) - ${policy.effect}`);
      });

      // Create a new custom policy
      console.log("\n➕ Creating a new ABAC policy:");
      const newPolicy = {
        name: "Weekend Device Restriction",
        description: "Restrict device write access for guests on weekends",
        resource: "device",
        action: "write",
        effect: "DENY",
        priority: 300,
        condition: {
          and: [
            { userRole: { in: ["guest"] } },
            { dayOfWeek: { in: ["saturday", "sunday"] } }
          ]
        }
      };

      const createResult = await this.broker.call("v1.cloud-authorization.createAbacPolicy", newPolicy);
      console.log(`   ✅ Policy created: ${createResult.policy.name}`);

      // Test the new policy
      console.log("\n🧪 Testing the new policy:");
      const testResult = await this.broker.call("v1.cloud-authorization.authorize", {
        userId: "guest123",
        resource: "device", 
        action: "write",
        context: {
          dayOfWeek: "saturday"
        }
      });

      console.log(`   Guest device control on weekend: ${testResult.authorized ? '✅ ALLOWED' : '❌ DENIED'}`);

      // Clean up - delete the test policy
      if (createResult.policy.id) {
        await this.broker.call("v1.cloud-authorization.deleteAbacPolicy", {
          policyId: createResult.policy.id
        });
        console.log("   🗑️ Test policy cleaned up");
      }

    } catch (error) {
      console.log(`   Error in policy management demo: ${error.message}`);
    }
  }

  /**
   * Run all demo scenarios
   */
  async runAllDemos() {
    await this.init();

    await this.demoTimeBasedAccess();
    await this.demoLocationBasedAccess(); 
    await this.demoDeviceOwnership();
    await this.demoEmergencyOverride();
    await this.demoBusinessHoursAutomation();
    await this.demoOfflineMode();
    await this.demoPolicyManagement();

    console.log("\n" + "=".repeat(60));
    console.log("🎉 All RBAC + ABAC demos completed!");
    console.log("=" .repeat(60));

    await this.broker.stop();
  }
}

// Run the demo if this file is executed directly
if (require.main === module) {
  const demo = new RbacAbacDemo();
  demo.runAllDemos().catch(console.error);
}

module.exports = RbacAbacDemo;
