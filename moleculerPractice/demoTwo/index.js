const { ServiceBroker } = require("moleculer");
const subscriber = require("./services/subscriber");
const NATS = require("nats");
const pino = require("pino")
const broker = new ServiceBroker({
    namespace: "inventory-broker-for-apples",
    nodeID: "shop-node-1",
    transporter: NATS.connect({ servers: "nats://localhost:4222" }),
    requestTimeout: 5000,
    api: {
      port: 3000
    }
});
subscriber();
broker.createService(require("./services/Inventory"));
broker.createService(require("./services/InventoryMonitor"));

broker.start().then(async () => {
    pino().info("Broker started and listening for requests...");
    try {
      pino().info(await broker.call("inventory.addItem", { item: "apple", quantity: 10 }));
      pino().info(await broker.call("inventory.addItem", { item: "banana", quantity: 20 }));
      pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: 15 }));
      pino().info("Fetching details for 'apple':");
      pino().info(await broker.call("inventory.getItem", { item: "apple" }));
      pino().info("Updating quantity for 'orange':");
      pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: 6 }));
      pino().info("Fetching all items in the inventory:");
      pino().info(await broker.call("inventory.getAllItems"));
      broker.stop();
      pino().info("Broker stopped.");
    } catch (err) {
      console.error("An error occurred during the workflow:", err);
    }
  });