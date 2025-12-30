import { JSONCodec, NatsConnection, Subscription, connect } from 'nats';

export interface NatsConfig {
  servers: string | string[];
  name?: string;
}

export async function connectNats(config: NatsConfig): Promise<NatsConnection> {
  return connect({ servers: config.servers, name: config.name });
}

export interface SubscribeOptions {
  queue?: string;
}

export async function subscribeJson<T>(
  nc: NatsConnection,
  subject: string,
  handler: (data: T) => Promise<void> | void,
  options?: SubscribeOptions
): Promise<Subscription> {
  const codec = JSONCodec<T>();
  const sub = nc.subscribe(subject, { queue: options?.queue });

  (async () => {
    for await (const msg of sub) {
      try {
        const data = codec.decode(msg.data);
        await handler(data as T);
      } catch (error) {
        console.error('Failed to handle NATS message', error);
      }
    }
  })();

  return sub;
}

export async function drainAndClose(nc: NatsConnection) {
  await nc.drain();
}
