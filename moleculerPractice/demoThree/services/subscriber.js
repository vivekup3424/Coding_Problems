const NATS = require("nats");
const fs = require("fs");
const path = require("path");

module.exports = (async () => {
  const LOG_FILE = path.join(__dirname, "nats-logs.txt");
  const writeLog = async (log) => {
    const timestamp = new Date().toISOString();
    const logEntry = `[${timestamp}] ${log}\n`;

    try {
      await fs.promises.appendFile(LOG_FILE, logEntry, "utf-8");
    } catch (err) {
      console.error("Failed to write log:", err);
    }
  };
  const nc = await NATS.connect({ servers: "nats://localhost:4222" });

  await writeLog("Connected to NATS!");

  nc.subscribe("inventory.updated", async (msg, reply, subject) => {
    const logMessage = `Received update on subject '${subject}': ${msg}`;
    console.log(logMessage); // Optional: For real-time monitoring
    await writeLog(logMessage);
  });
  await writeLog(`Listening for updates on 'inventory.updated'...`);
  process.on("SIGINT", async () => {
    await writeLog("\nClosing NATS connection...");
    await nc.drain();
    process.exit(0);
  });
});
