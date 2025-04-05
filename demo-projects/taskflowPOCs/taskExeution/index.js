const { ServiceBroker } = require("moleculer");
const { getchannelsmiddleware } = require("./middleware.js");
const paymentService = require("./payments.service.js")
const broker = new ServiceBroker({
    nodeID: "node-1",
    namespace: "METRO",
    transporter: "NATS", // Change as per your setup
    tracing: true,
    middlewares: [getchannelsmiddleware({ namespace: "METRO" })]
});

broker.createService(paymentService)

broker.start().then(async () => {
    console.log("Broker started!");

    // Manually sending a message to the channel
    await broker.sendToChannel("default.options.topic", { amount: 100 }, {
        meta: { loggedInUser: "user123", role: "admin" }
    });

    console.log("Message sent to channel.");
});

