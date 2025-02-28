import { ServiceBroker } from "moleculer";
const broker = new ServiceBroker({
  nodeID: "joji",
  namespace: "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0",
  transporter: {
    type: "NATS",
    options: {
      url: "nats://10.1.4.238:9769",
      token: "keus-iot-platform",
    },
  }, //add auth token of keus-iot-platform
  logLevel: "debug",
  requestTimeout: 1 * 1000, //5 seconds,
  metadata: {
    region: "eu-west-1",
  },
  retryPolicy: {
    enabled: true,
  },
});
broker
  .start()
  .then(async () => {
    try {
      broker
        .ping()
        .then((res) => broker.logger.info(res))
        .catch((err) => {
          broker.logger.error(err);
        });
    } catch (error) {}
  })
  .catch((err) => {
    console.log("Error during starting the broker=>", err);
  })
  .finally(() => {
    console.log("Final execution done");
  });
