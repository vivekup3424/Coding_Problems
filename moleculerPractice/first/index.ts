import { ServiceBroker } from "moleculer";

const newServiceBroker = new ServiceBroker();
newServiceBroker.createService({
    name: "Hello",
    actions: {
        hello(_) {
            return "Hello Moleculer";
        }
    }
})
newServiceBroker.start().then(()=>{
    newServiceBroker.call("Hello.hello").then((response)=>{
        console.log(`response = ${response}`)
    })
})