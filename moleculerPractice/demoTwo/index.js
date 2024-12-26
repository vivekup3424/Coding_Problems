const { ServiceBroker } = require("moleculer");
const NATS = require("nats");
const broker = new ServiceBroker({
  namespace: "inventory-broker",
  nodeID: "shop-node-2",
  transporter: {
    type: "NATS",
    options: {
      url: "nats://localhost:6969",
      token: "keus-iot-platform",
    }
  },
});

broker.start().then(async () => {
  console.log("Broker 2 started")
});