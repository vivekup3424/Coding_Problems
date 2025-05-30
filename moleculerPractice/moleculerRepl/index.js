const { ServiceBroker } = require("moleculer");

(async function() {
    async function getSiteId() {
        const nodeConfigRes = await fetch("http://172.24.128.1:3000/keus/v1/node_configuration/GetNodeConfig");
        const responseData = await nodeConfigRes.json();
        const siteId = responseData?.nodeConfig?.siteInfo?.siteId;
        if (!siteId) {
            throw new Error("Failed to get siteId");
        }

        return siteId;
    }

    const siteId = await getSiteId();
    let broker = new ServiceBroker({ namespace: siteId });

    // Switch to REPL mode
    broker.repl();
})()
