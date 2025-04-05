module.exports = {
    name: "payments",

    actions: {
        processPayment: {
            async handler(ctx) {
                return `Processing payment for user: ${ctx.meta.loggedInUser}`;
            }
        }
    },

    channels: {
        "default.options.topic": {
            context: true, // Enables the Moleculer context in channel handlers
            async handler(ctx) {
                console.log("Received message:", ctx.params);
                console.log("Metadata:", ctx.meta);

                if (ctx.meta.loggedInUser) {
                    // Call an action with the same meta
                    const response = await ctx.call("payments.processPayment", ctx.params, { meta: ctx.meta });
                    console.log("Action Response:", response);
                }
            }
        }
    }
};

