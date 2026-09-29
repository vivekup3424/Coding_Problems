import { buildContainer } from "./container.js";
import { ensureIndexes } from "./db-indexes.js";

const container = buildContainer();
const { config, mongoClient, mongoDb, app } = container.cradle;

await mongoClient.connect();
console.log("Connected to MongoDB");

await ensureIndexes(mongoDb);
console.log("MongoDB indexes ready");

const server = app.listen(config.port, config.host, () => {
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
