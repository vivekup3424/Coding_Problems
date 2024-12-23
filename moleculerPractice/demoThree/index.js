const { ServiceBroker } = require("moleculer");
const subscriber = require("./services/subscriber");
const NATS = require("nats");
const pino = require("pino")
const broker = new ServiceBroker({
  namespace: "inventory-broker",
  nodeID: "shop-node-3",
  transporter: {
    type: "NATS",
    options: {
      url: "nats://10.1.4.196:6970",
      token: "keus-iot-platform",
    }
  },
  requestTimeout: 5000,
  api: {
    port: 3000
  }
});
broker.createService(require("./services/Joker"));

broker.start().then(async () => {
  pino().info("Broker started and listening for requests...");
  try {
    pino().info(await broker.call("inventory.addItem", { item: "apple", quantity: 8 }));
    pino().info(await broker.call("inventory.addItem", { item: "banana", quantity: -43 }));
    pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: -76 }));
    pino().info("Fetching details for 'apple':");
    pino().info(await broker.call("inventory.getItem", { item: "apple" }));
    pino().info("Updating quantity for 'orange':");
    pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: 23 }));
    pino().info("Fetching all items in the inventory:");
    pino().info(await broker.call("inventory.getAllItems"));
  } catch (err) {
    console.error("An error occurred during the workflow:", err);
  }
});