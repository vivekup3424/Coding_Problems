import 'dotenv/config';
import path from 'path';
import process from 'process';
import { fileURLToPath } from 'url';
import { buildEngine } from './rules/engine.js';
import { loadRulesFromFile, watchRules } from './rules/load-rules.js';
import { motionEventSchema } from './types.js';
import { connectNats, drainAndClose, subscribeJson } from './nats/client.js';
import { EngineRef, handleMotionEvent } from './handlers/on-message.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

async function main() {
  const rulesPath = process.env.RULES_PATH ?? path.join(__dirname, 'rules', 'rules.json');
  const natsServers = (process.env.NATS_SERVERS ?? 'nats://localhost:4222')
    .split(',')
    .map(server => server.trim())
    .filter(Boolean);
  const natsSubject = process.env.NATS_SUBJECT ?? 'events.anomaly';
  const natsQueue = process.env.NATS_QUEUE;

  const rules = await loadRulesFromFile(rulesPath);
  const engineRef: EngineRef = { current: buildEngine(rules) };
  console.log(`Loaded ${rules.length} rules from ${rulesPath}`);

  const stopWatching = watchRules(
    rulesPath,
    updatedRules => {
      engineRef.current = buildEngine(updatedRules);
      console.log(`Reloaded ${updatedRules.length} rules from ${rulesPath}`);
    },
    {
      onError: error => console.error('Failed to reload rules', error)
    }
  );

  const nc = await connectNats({ servers: natsServers });
  console.log(`Connected to NATS at ${natsServers.join(',')}`);

  await subscribeJson<unknown>(
    nc,
    natsSubject,
    async payload => {
      console.log("incoming payload = ", payload)
      const parsed = motionEventSchema.safeParse(payload);
      if (!parsed.success) {
        console.error('Invalid camera motion event', parsed.error.flatten());
        return;
      }
      await handleMotionEvent(engineRef, parsed.data);
    },
    { queue: natsQueue }
  );

  const shutdown = async () => {
    console.log('Shutting down...');
    stopWatching();
    await drainAndClose(nc);
    process.exit(0);
  };

  process.on('SIGINT', shutdown);
  process.on('SIGTERM', shutdown);
}

main().catch(error => {
  console.error('Fatal error', error);
  process.exit(1);
});
