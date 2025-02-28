module.exports = {
    name: "payments",
    actions: {
        hello(){
            console.log("za worudo")
        }
    },
    channels :{
        //here consumer group is the service's full name
        async "order.created"(payload:any){
            console.log("payload=",payload)
        },
        "payment.processed":{
            group:"other",
            async handler(payload:any){
                console.log("Payment Processed", payload)
            }
        }
    }
}