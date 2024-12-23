const { ServiceBroker } = require("moleculer");
const subscriber = require("./services/subscriber");
const pino = require("pino")

const broker = new ServiceBroker({
  namespace: "inventory-broker",
  nodeID: "shop-node-1",
  transporter: {
    type: "NATS",
    options: {
      url: "nats://10.1.4.196:6969",
      token: "keus-iot-platform",
    }
  },
});

// subscriber();
broker.createService(require("./services/Inventory"));
broker.createService(require("./services/InventoryMonitor"));
nodes = []
broker.createService({
  name: "networkMonitor",
 events: {
    "$node.connected"(node) {
      nodes.push(node);
      console.log(`Node connected: ${node.id}`);
    },
    
    "$node.disconnected"(node) {
      const index = nodes.findIndex(n => n.id === node.id);
      if (index > -1) {
        nodes.splice(index, 1);
      }
      console.log(`Node disconnected: ${node.id}`);
    }
  }
});

broker.start().then(async () => {
  pino().info("Broker started and listening for requests...");
  pino().info(`Services are creating on node: ${broker.nodeID}`)
  broker.call("$node.list").then(res => console.log(res));
  broker.call("createService")
  // broker.
  // try {
  //   pino().info(await broker.call("inventory.addItem", { item: "apple", quantity: 10 }));
  //   pino().info(await broker.call("inventory.addItem", { item: "banana", quantity: 20 }));
  //   pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: 15 }));
  //   pino().info("Fetching details for 'apple':");
  //   pino().info(await broker.call("inventory.getItem", { item: "apple" }));
  //   pino().info("Updating quantity for 'orange':");
  //   pino().info(await broker.call("inventory.addItem", { item: "orange", quantity: 6 }));
  //   pino().info("Fetching all items in the inventory:");
  //   pino().info(await broker.call("inventory.getAllItems"));
  // } catch (err) {
  //   console.error("An error occurred during the workflow:", err);
  // }
});