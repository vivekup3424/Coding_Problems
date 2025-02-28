import { ServiceBroker } from "moleculer";
const broker = new ServiceBroker({
    logger: true,
});

broker.createService({
    name: "test",
    actions: {
        fail: {
            retryPolicy: {
                enabled: true,   // Enable retries
                retries: 3,      // Max retries
                delay: 1000,     // Delay (1 second) between retries
                maxDelay: 5000,  // Maximum delay (5 seconds)
                factor: 2,       // Exponential backoff (1s, 2s, 4s)
                check: (err) => err.retryable !== false, // Only retry retryable errors
            },
            async handler(ctx) {
                console.log("Executing action...");
                throw new Error("Temporary error, will retry!");
            }
        }
    }
});

async function main() {
    await broker.start();
    try {
        await broker.call("test.fail");
    } catch (err) {
        console.error("Final Error After Retries:", err.message);
    }
}

main();

