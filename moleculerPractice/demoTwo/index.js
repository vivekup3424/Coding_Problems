const { ServiceBroker } = require("moleculer");
const subscriber = require("./services/subscriber");
const NATS = require("nats");
const pino = require("pino")
const broker = new ServiceBroker({
    namespace: "inventory-broker-for-apples",
    nodeID: "shop-node-2",
    transporter: NATS.connect({ servers: "nats://localhost:4222" }),
    requestTimeout: 5000,
    api: {
      port: 3000
    }
});

broker.start().then(() => {
  // Start the loop after broker starts
  pino().info("Broker started and listening for requests...");

  // Function to execute the workflow with a delay of 2 seconds
  const executeWorkflow = async () => {
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
    } catch (err) {
      console.error("An error occurred during the workflow:", err);
    }
  };

  // Use setInterval to repeatedly call the function every 2 seconds
  const intervalId = setInterval(async () => {
    await executeWorkflow();
    clearInterval(intervalId); // Stop the loop after one iteration
  }, 2000); // 2000 milliseconds = 2 seconds
}).catch(err => {
  console.error("Error starting broker:", err);
});
