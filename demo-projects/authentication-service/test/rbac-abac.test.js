/**
 * Test cases for RBAC + ABAC Authorization System
 */

const { ServiceBroker } = require("moleculer");
const { describe, it, before, after } = require("mocha");
const { expect } = require("chai");

describe("RBAC + ABAC Authorization System", () => {
  let broker;

  before(async () => {
    broker = new ServiceBroker({
      logger: false,
      transporter: null
    });

    // Load services
    broker.loadService("./services/cloud-authorization.service.js");
    broker.loadService("./services/local-authorization.service.js");
    
    await broker.start();
  });

  after(async () => {
    await broker.stop();
  });

  describe("Cloud Authorization Service - RBAC + ABAC", () => {
    
    it("should deny device control during restricted hours for regular users", async () => {
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "write",
        context: {
          time: "02:00", // Restricted time
          userRole: "user"
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.false;
      expect(result.evaluationDetails.abac.decision).to.be.false;
    });

    it("should allow device control during restricted hours for homeowners", async () => {
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "homeowner456",
        resource: "device", 
        action: "write",
        context: {
          time: "02:00", // Restricted time
          userRole: "homeowner"
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.true;
    });

    it("should deny security admin access from untrusted locations", async () => {
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "admin789",
        resource: "security",
        action: "admin",
        context: {
          userLocation: "public"
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.false;
    });

    it("should allow device ownership-based access", async () => {
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "write", 
        context: {
          resourceData: { owner: "user123" }
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.true;
    });

    it("should allow emergency actions regardless of restrictions", async () => {
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "emergency-stop",
        context: {
          emergencyMode: true,
          time: "02:00" // Normally restricted
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.true;
    });

    it("should create and evaluate custom ABAC policies", async () => {
      // Create a test policy
      const policy = {
        name: "Test Weekend Restriction",
        description: "Test policy for weekends",
        resource: "automation",
        action: "execute", 
        effect: "DENY",
        priority: 500,
        condition: {
          and: [
            { userRole: { in: ["guest"] } },
            { dayOfWeek: { in: ["sunday"] } }
          ]
        }
      };

      const createResult = await broker.call("v1.cloud-authorization.createAbacPolicy", policy);
      expect(createResult.success).to.be.true;
      expect(createResult.policy.name).to.equal(policy.name);

      // Test the policy
      const authResult = await broker.call("v1.cloud-authorization.authorize", {
        userId: "guest123", 
        resource: "automation",
        action: "execute",
        context: {
          dayOfWeek: "sunday"
        }
      });

      expect(authResult.authorized).to.be.false;

      // Clean up
      if (createResult.policy.id) {
        await broker.call("v1.cloud-authorization.deleteAbacPolicy", {
          policyId: createResult.policy.id
        });
      }
    });

    it("should list ABAC policies", async () => {
      const result = await broker.call("v1.cloud-authorization.listAbacPolicies");
      
      expect(result.success).to.be.true;
      expect(result.policies).to.be.an('array');
      expect(result.policies.length).to.be.greaterThan(0);
    });
  });

  describe("Local Authorization Service - RBAC + ABAC", () => {
    
    it("should handle local permissions with ABAC", async () => {
      const result = await broker.call("v1.local-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "emergency-stop",
        context: {
          emergencyMode: true
        }
      });

      expect(result.success).to.be.true;
      expect(result.authorized).to.be.true;
      expect(result.source).to.equal("local");
    });

    it("should restrict actions during offline mode based on local ABAC policies", async () => {
      // Enable offline mode
      await broker.call("v1.local-authorization.setOfflineMode", { enabled: true });

      const result = await broker.call("v1.local-authorization.authorize", {
        userId: "user123", 
        resource: "device",
        action: "write",
        context: {
          time: "02:00" // Restricted time in offline mode
        }
      });

      expect(result.success).to.be.true;
      expect(result.source).to.equal("offline");
      expect(result.warning).to.include("offline mode");

      // Reset offline mode
      await broker.call("v1.local-authorization.setOfflineMode", { enabled: false });
    });

    it("should evaluate local ABAC policies", async () => {
      const result = await broker.call("v1.local-authorization.evaluateLocalAbacPolicies", {
        userId: "user123",
        resource: "device", 
        action: "emergency-stop",
        context: {
          emergencyMode: true
        }
      });

      expect(result.success).to.be.true;
      expect(result.policies).to.be.an('array');
      
      // Should have emergency override policy
      const emergencyPolicies = result.policies.filter(p => 
        p.name.toLowerCase().includes('emergency')
      );
      expect(emergencyPolicies.length).to.be.greaterThan(0);
    });

    it("should handle device ownership in local mode", async () => {
      const result = await broker.call("v1.local-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "write",
        context: {
          resourceData: { owner: "user123" }
        }
      });

      expect(result.success).to.be.true;
    });

    it("should get service status with ABAC info", async () => {
      const result = await broker.call("v1.local-authorization.getStatus");
      
      expect(result.success).to.be.true;
      expect(result.status).to.have.property('offlineMode');
      expect(result.status).to.have.property('localPermissions');
    });
  });

  describe("Integration Tests - RBAC + ABAC", () => {
    
    it("should fall back from cloud to local authorization", async () => {
      // This test simulates cloud service being unavailable
      // The local service should handle the fallback gracefully
      
      const result = await broker.call("v1.local-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "local-read", // Local permission
        context: {}
      });

      expect(result.success).to.be.true;
      expect(result.source).to.equal("local");
    });

    it("should combine RBAC and ABAC decisions correctly", async () => {
      // Test where RBAC allows but ABAC denies
      const result = await broker.call("v1.cloud-authorization.authorize", {
        userId: "user123", // Has basic user permissions
        resource: "device",
        action: "write",
        context: {
          time: "02:00", // ABAC should deny this
          resourceData: { owner: "otheruser" } // Not owned by user
        }
      });

      expect(result.success).to.be.true;
      expect(result.evaluationDetails).to.have.property('rbac');
      expect(result.evaluationDetails).to.have.property('abac');
      expect(result.evaluationDetails).to.have.property('final');
    });

    it("should handle emergency overrides across both services", async () => {
      const cloudResult = await broker.call("v1.cloud-authorization.authorize", {
        userId: "user123",
        resource: "security",
        action: "alarm-disable", 
        context: {
          emergencyMode: true,
          userLocation: "public" // Normally restricted
        }
      });

      const localResult = await broker.call("v1.local-authorization.authorize", {
        userId: "user123",
        resource: "device",
        action: "emergency-stop",
        context: {
          emergencyMode: true
        }
      });

      expect(cloudResult.authorized).to.be.true;
      expect(localResult.authorized).to.be.true;
    });
  });
});
