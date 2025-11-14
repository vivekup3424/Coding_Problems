import Moleculer from 'moleculer';

const broker = new Moleculer.ServiceBroker({
    nodeID: "node-1",
    transporter: {
        type: "NATS",
        options: {
            url: "nats://kioti-nats-1-dev.keus.in:6969",
            token: "keus-ops-nats",
        }
    }
})

class ServiceA extends Moleculer.Service {
    constructor(broker) {
        super(broker);
        this.parseServiceSchema({
            name: "serviceA",
            actions: {
                hello() {
                    return "Hello from Service A";
                }
            }
        });
    }
}
class ServiceB extends Moleculer.Service {
    constructor(broker) {
        super(broker);
        this.parseServiceSchema({
            name: "serviceB",
            actions: {
                hello() {
                    return "Hello from Service B";
                }
            }
        });
    }
}

class ServiceC extends Moleculer.Service {
    constructor(broker) {
        super(broker);
        this.parseServiceSchema({
            name: "serviceC",
            actions: {
                hello() {
                    return "Hello from Service C";
                }
            }
        });
    }
}

broker.createService(ServiceA);
broker.createService(ServiceB);
broker.createService(ServiceC);

broker.start().then(() => {
    console.log("Broker started");
    broker.call("$node.services").then((services)=> {
        console.log("Registered services:\n", JSON.stringify(services, null, 2));
    })
    // broker.repl();
})
