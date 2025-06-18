import Moleculer from "moleculer";
class NotificationService extends Moleculer.Service{
    private broker: Moleculer.ServiceBroker;
    constructor(broker: Moleculer.ServiceBroker){
        this.broker = broker;
        super(broker);
        this.parseServiceSchema({
            name: "notification-service",
            version: "1.0.0",
            channels: {
                "notification.created": 
            }
        })
    }
}