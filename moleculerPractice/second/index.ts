import { ServiceBroker } from "moleculer";
const HTTPServer = require("moleculer-web");

const brokerNode1 = new ServiceBroker({
    nodeID: "node1",
    transporter: "NATS",
})

brokerNode1.createService({
    name: "gateway",
    mixins: [HTTPServer],
    
})