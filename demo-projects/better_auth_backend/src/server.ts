import { buildContainer } from "./container.js";

const container = buildContainer();
const { config, mongoClient, httpApp } = container.cradle;

await mongoClient.connect();
console.log("Connected to MongoDB");

const server = httpApp.listen(config.port, config.host, () => {
  console.log(`Server listening on http://${config.host}:${config.port}`);
});

async function shutdown(signal: string) {
  console.log(`${signal} received, shutting down`);
  server.close();
  await container.dispose();
  process.exit(0);
}

process.once("SIGINT", () => void shutdown("SIGINT"));
process.once("SIGTERM", () => void shutdown("SIGTERM"));
