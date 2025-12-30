import process from 'process';
import { connect, JSONCodec } from 'nats';

function toBool(value: string | undefined, fallback: boolean): boolean {
  if (value === undefined) return fallback;
  return value.toLowerCase() === 'true';
}

async function main() {
  const servers = (process.env.NATS_SERVERS ?? 'nats://localhost:4222')
    .split(',')
    .map(s => s.trim())
    .filter(Boolean);
  const subject = process.env.NATS_SUBJECT ?? 'camera.motion';

  const now = new Date();
  const event = {
    _id: process.env.EVENT_ID ?? `evt-${now.getTime()}`,
    event_id: process.env.EVENT_ID ?? 'cameras.motion.person',
    event_type: process.env.EVENT_TYPE ?? 'cameras',
    hour_of_day: Number(process.env.HOUR_OF_DAY ?? now.getHours()),
    day_of_week: Number(process.env.DAY_OF_WEEK ?? now.getDay()),
    count_last_24h: Number(process.env.COUNT_LAST_24H ?? 30),
    count_last_7d: Number(process.env.COUNT_LAST_7D ?? 12),
    count_last_30d: Number(process.env.COUNT_LAST_30D ?? 20),
    count_last_90d: Number(process.env.COUNT_LAST_90D ?? 50),
    count_all_time: Number(process.env.COUNT_ALL_TIME ?? 120),
    last_occurred: Number(process.env.LAST_OCCURRED ?? Date.now())
  };

  const nc = await connect({ servers });
  const codec = JSONCodec();

  console.log(`Publishing to ${subject} on ${servers.join(',')}:`, event);
  nc.publish(subject, codec.encode(event));

  await nc.drain();
}

main().catch(err => {
  console.error('Failed to publish event', err);
  process.exit(1);
});
