import { ServiceBroker } from "moleculer";
const broker = new ServiceBroker();

(async () => {
    await broker.start()
    await broker.createService({
        name: "math",
        settings: {
            customParam1: "Hello from settings",
            customParam2: 42,
            customConfig: {
                debug: true,
                timeout: 5000
            }
        },
        actions: {
            add(ctx) {
                return Number(ctx.params.a) + Number(ctx.params.b)
            }
        },
        created() {
            console.log("Service created")
            console.log(this)
        },
        started() {
            console.log("Service started")
        },
        stopped() {
            console.log("Service stopped")
        }
    })
    await broker.waitForServices(["math"])
    const response = await broker.call("math.add", { a: 5, b: 10 })
    console.log(response)
})()