const { ServiceBroker } = require("moleculer");
const subscriber = require("./services/subscriber");

const nodes = new Set(); // Using Set for more efficient node tracking

const broker = new ServiceBroker({
  namespace: "inventory-broker",
  nodeID: "shop-node-1",
  transporter: {
    type: "NATS",
    options: {
      url: "nats://localhost:6969",
      token: "keus-iot-platform",
    }
  },
  // Add this logger configuration
  logger: {
    type: "Console",
    options: {
      // Pino options if needed
    }
  }
});

// Create a dedicated service for network monitoring
const NetworkMonitorService = {
  name: "networkMonitor",
  
  events: {
    // Event when any node connects
    "$node.connected"({ sender, node }) {
      nodes.add(node.id);
      console.log(`Node connected: ${node.id}`);
      // You can add additional logic here
      this.broker.broadcast("node.status", { 
        type: "connected", 
        nodeId: node.id,
        totalNodes: nodes.size
      });
    },

    // Event when any node disconnects
    "$node.disconnected"({ sender, node }) {
      nodes.delete(node.id);
      console.log(`Node disconnected: ${node.id}`);
      // You can add additional logic here
      this.broker.broadcast("node.status", {
        type: "disconnected",
        nodeId: node.id,
        totalNodes: nodes.size
      });
    }
  },

  // Add methods to query node status
  actions: {
    getConnectedNodes() {
      return Array.from(nodes);
    },
    
    getNodeCount() {
      return nodes.size;
    }
  },

  // Lifecycle hooks
  started() {
    console.log("Network monitor service started");
  },

  stopped() {
    console.log("Network monitor service stopped");
    nodes.clear();
  }
};

// Register your services
broker.createService(require("./services/Inventory"));
broker.createService(require("./services/InventoryMonitor"));
broker.createService(NetworkMonitorService);

// Start the broker
broker.start()
  .then(async () => {
    console.log("Broker started and listening for requests...");
    console.log(`Services are running on node: ${broker.nodeID}`);
    
    // Get initial node list
    try {
      const nodeList = await broker.call("$node.list");
      console.log('Connected nodes:', nodeList);
      
      // Initialize nodes Set with existing nodes
      nodeList.forEach(node => nodes.add(node.id));
      
      // You can also test the monitoring service
      const connectedNodes = await broker.call("networkMonitor.getConnectedNodes");
      console.log('Current connected nodes:', connectedNodes);
    } catch (error) {
      logger.error('Error getting node list:', error);
    }
  })
  .catch(error => {
    logger.error('Failed to start broker:', error);
    process.exit(1);
  });

// Graceful shutdown
process.on('SIGTERM', async () => {
  await broker.stop();
  process.exit(0);
});