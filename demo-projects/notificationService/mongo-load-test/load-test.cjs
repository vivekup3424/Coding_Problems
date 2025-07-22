const { MongoClient } = require("mongodb");
const { v4: uuidv4 } = require("uuid");
const { performance } = require("perf_hooks");

const uri = "mongodb://10.1.4.81:27017";
const dbName = "notificationDB";
const inboxCollectionName = "notificationInboxes";
const notificationCollectionName = "notifications";
const INBOX_COUNT = 50;
const NOTIFICATIONS_PER_MINUTE = 500;
const TEST_DURATION_MS = 5 * 60 * 1000;

async function main() {
  const client = new MongoClient(uri);
  await client.connect();
  const db = client.db(dbName);

  const inboxCollection = db.collection(inboxCollectionName);
  const notificationCollection = db.collection(notificationCollectionName);

  await inboxCollection.createIndexes([
    { key: { inboxId: 1, readAt: -1, createdAt: -1 } },
    { key: { expiresAt: 1 }, expireAfterSeconds: 0 },
  ]);
  await notificationCollection.createIndexes([
    { key: { createdAt: 1 }, expireAfterSeconds: 60 * 60 * 24 * 7 }, // 7 days
  ]);

  console.log("Indexes created. Starting load test...\n");

  const startTime = Date.now();
  const stats = {
    notificationCreated: [],
    inboxAdded: [],
    markedRead: [],
    expiredCleaned: [],
    unreadFetched: [],
  };

  function recordLatency(name, start) {
    const ms = performance.now() - start;
    stats[name].push(ms);
    return ms.toFixed(2);
  }

  async function createNotification() {
    const id = uuidv4();
    const doc = {
      _id: id,
      notificationId: id,
      createdAt: new Date(),
      userIdentifier: `user-${Math.floor(Math.random() * 1000)}`,
      type: "email",
      content: { subject: "Test", body: "Sample content" },
      deliveryStatus: "PENDING",
    };
    const t0 = performance.now();
    await notificationCollection.insertOne(doc);
    console.log(`✅ Created notification in ${recordLatency("notificationCreated", t0)} ms`);
    return doc;
  }

  async function addToInbox(notificationId) {
    const inboxId = `inbox-${Math.floor(Math.random() * INBOX_COUNT)}`;
    const userId = `user-${Math.floor(Math.random() * 1000)}`;
    const now = new Date();
    const inboxEntry = {
      _id: uuidv4(),
      inboxId,
      userId,
      notificationId,
      createdAt: now,
      expiresAt: new Date(now.getTime() + 60 * 2 * 10 * 1000 + Math.random() * 120_000), // 20-22 minutes
      readAt: null,
    };
    const t0 = performance.now();
    try {
      await inboxCollection.insertOne(inboxEntry);
      console.log(`📥 Inbox insert in ${recordLatency("inboxAdded", t0)} ms`);
    } catch (err) {
      console.error("❌ Inbox insert failed:", err.message);
    }
  }

  async function markRead() {
    const t0 = performance.now();
    const result = await inboxCollection.findOneAndUpdate(
      { readAt: null },
      { $set: { readAt: new Date() } }
    );
    if (result.value) {
      console.log(`✅ Marked read in ${recordLatency("markedRead", t0)} ms`);
    }
  }

  async function cleanupExpired() {
    const now = new Date();
    const t0 = performance.now();
    const result = await inboxCollection.deleteMany({ expiresAt: { $lt: now } });
    const latency = recordLatency("expiredCleaned", t0);
    if (result.deletedCount > 0) {
      console.log(`🧹 Cleaned ${result.deletedCount} expired entries in ${latency} ms`);
    }
  }

  async function fetchUnread() {
    const inboxId = `inbox-${Math.floor(Math.random() * INBOX_COUNT)}`;
    const t0 = performance.now();
    const result = await inboxCollection
      .find({ inboxId, readAt: null })
      .sort({ createdAt: -1 })
      .limit(20)
      .toArray();
    console.log(`📄 Fetched ${result.length} unread in ${recordLatency("unreadFetched", t0)} ms`);
  }

  function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }

  async function runWorker() {
    while (Date.now() - startTime < TEST_DURATION_MS) {
      const notif = await createNotification();
      await addToInbox(notif.notificationId);

      if (Math.random() < 0.3) await markRead();
      if (Math.random() < 0.2) await fetchUnread();
      if (Math.random() < 0.1) await cleanupExpired();

      await sleep(60_000 / NOTIFICATIONS_PER_MINUTE);
    }
  }

  const NUM_WORKERS = 10;
  await Promise.all(Array.from({ length: NUM_WORKERS }, runWorker));

  console.log("\n🏁 Load test completed. Latency summary:");

  for (const [operation, timings] of Object.entries(stats)) {
    if (timings.length === 0) continue;
    const avg = timings.reduce((a, b) => a + b, 0) / timings.length;
    const p95 = timings.sort((a, b) => a - b)[Math.floor(0.95 * timings.length)];
    console.log(
      `- ${operation.padEnd(18)}: avg ${avg.toFixed(2)} ms | p95 ${p95.toFixed(2)} ms | count ${timings.length}`
    );
  }

  await client.close();
}

main().catch(console.error);
