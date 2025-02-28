import { ServiceBroker } from "moleculer";
const broker = new ServiceBroker({
  nodeID: "joji",
  namespace: "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0",
  transporter: "nats://localhost:4222",
  logLevel: "debug",
  requestTimeout: 1 * 1000, //5 seconds,
  metadata: {
    region: "eu-west-1",
  },
});
// broker
//   .start()
//   .then(async () => {
//     const response = await broker.call("$node.list");
//     try {
//       broker
//         .ping("Qjrirk4", 1000)
//         .then((res) => broker.logger.info(res))
//         .catch((err) => {
//           broker.logger.error(err);
//         });
//     } catch (error) {}
//     broker.logger.info(response);
//   })
//   .catch((err) => {
//     console.log("Error during starting the broker=>", err);
//   })
//   .finally(() => {
//     console.log("Final execution done");
//   });
broker.start().then(async () => {
  await broker.repl();
});
