import { jetstreamManager, JetStreamManager } from "@nats-io/jetstream";
import { NatsConnection } from "@nats-io/nats-core/lib/core";
import { connect } from "@nats-io/transport-node";

const nc: NatsConnection = await connect({ servers: ["localhost:4269"] });
const jsm: JetStreamManager = await jetstreamManager(nc);

(async () => {
    for await (const streamInfo of jsm.streams.list()) {
        console.log(streamInfo)
    }
})()
const myStream = "mystream"
const mysubject = "mystream.subject"
await jsm.streams.add({name: myStream, subjects: [mysubject]})
nc.publish(mysubject, JSON.stringify({ count: 1 }))
await nc.drain();