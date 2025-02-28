const ChannelsMiddleware = require("@moleculer/channels").Middleware;
module.exports = {
    logger: true,
    middlewares: [
        ChannelsMiddleware({
            adapter: "nats://10.1.4.128:6969"
        })
    ],
    metrics: false,
}
