import Moleculer from "moleculer";

export class MoleculerBrokerAdapter {

    private broker: Moleculer.ServiceBroker

    constructor(brokerConfig: Moleculer.BrokerOptions) {
        this.broker = new Moleculer.ServiceBroker(brokerConfig)
    }

    async connectBrokerToNats({ host, namespace, port, token, nodeId}: { namespace: string; nodeId: string; host: string; port: number; token: string;}) {
        try{

            if(this.broker.namespace){
                return
            }

            if (!namespace) {
                throw new Error("cannot start broker without namespace")
            }
    
            const _broker = this.broker
    
            this.broker = new Moleculer.ServiceBroker({
                namespace: namespace,
                nodeID: nodeId,
                transporter: {
                    type: "NATS",
                    options: {
                        servers: [`nats://${host}:${port}`],
                        token: token,
                        reconnect: true,
                        maxReconnectAttempts: -1,
                        waitOnFirstConnect: true,
                        noRandomize: true
                    },
                },
                logger: {
                    type: "Pino",
                    options: {
                        // Logging level
                        level: "warn",
                        pino: {
                            options: null,
                        }
                    }
                },
            })
    
            _broker.services.forEach(async service => {
                try {
                    await _broker.destroyService(service.schema);
                    await this.broker.createService(service.schema);
                } catch (err) {
                    console.error("ERROR WHILE CREATING MOLECULAR SERVICE: ", err)
                }
            })
    
            await _broker.stop()
            await this.broker.start()
        }catch(err){
            console.error("Failed to start cloud broker: ", err)
        }
    }

    getBroker() {
        return this.broker
    }

    async init() {
        await this.broker.start()
    }
}