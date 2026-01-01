import process from 'process';
import { connect, JSONCodec } from 'nats';

async function main() {
  const servers = ['nats://localhost:4222'];
  const subject = 'events.anomaly';

  const event = {
    eventId: 'cameras.motion.person',
    eventType: 'cameras',
    zone: 'front-door',
    timestamp: new Date()
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
