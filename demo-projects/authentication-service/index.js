const { ServiceBroker } = require("moleculer");
const config = require("./moleculer.config");

// Create broker
const broker = new ServiceBroker(config);

// Load services
broker.loadServices("services", "**/*.service.js");

// Start server
broker.start()
  .then(() => {
    console.log("🚀 Authentication & Authorization Platform started successfully!");
    console.log("Available services:");
    broker.registry.getServiceList({ onlyAvailable: true }).forEach(service => {
      console.log(`  - ${service.name} (v${service.version || "1"})`);
    });
  })
  .catch(err => {
    console.error("❌ Error starting broker:", err);
    process.exit(1);
  });

// Graceful shutdown
process.on("SIGINT", () => {
  console.log("\n🛑 Gracefully shutting down...");
  broker.stop()
    .then(() => {
      console.log("✅ Services stopped successfully");
      process.exit(0);
    })
    .catch(err => {
      console.error("❌ Error stopping services:", err);
      process.exit(1);
    });
});
