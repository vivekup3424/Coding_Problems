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
      url: "nats://localhost:6971",
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
  console.log("Broker 3 started")
});