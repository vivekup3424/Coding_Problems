import { NatsConnection, Subscription,Msg} from "@nats-io/nats-core/lib/core";
import {jetstream, jetstreamManager, JetStreamManager} from "@nats-io/jetstream"
import { connect } from "@nats-io/transport-node";
import pino from "pino";

const logger = pino({
    level: 'debug',
    transport: {
        target: 'pino-pretty',
        options: {
            colorize: true,
        }
    }
});

async function main() {
    let nc: NatsConnection;
    let jsm: JetStreamManager;

    try {
        logger.debug("Connecting to NATS server...");
        nc = await connect({ servers: ["localhost:4269"] }); // Default NATS port is 4222
        jsm = await jetstreamManager(nc);
        logger.debug("Connected successfully!");
        const timeSubscriber = nc.subscribe("time");
        logger.debug("Listening for subjects ... %s", timeSubscriber.getSubject());
        for await (const msg of timeSubscriber){
            logger.info(`time subject = %s`, msg.subject);
        }
        for(let i = 0; i < 10; i++){
            nc.publish("time", JSON.stringify({reply: "Time Request"}))
        }

        
    } catch (error) {
        logger.error("Connection failed: %s", error instanceof Error ? error.message : String(error));
        return;
    }
    
    try {
        await nc.drain();
        logger.debug("Connection closed gracefully");
    } catch (error) {
        logger.error("Error closing connection: %s", error instanceof Error ? error.message : String(error));
        return;
    }
}

main().catch(console.error);