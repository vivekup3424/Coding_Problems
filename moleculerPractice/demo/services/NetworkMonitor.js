module.exports  = {
  name: "NodeMonitor",
  actions: {
    listNodes(ctx) {
      return nodes;
    },
  },
  events: {
    "$node.connected"(node) {
      nodes.push(node);
      this.logger.info(`Node connected: ${node.id}`);
    },
    "$node.disconnected"(node) {
      const index = nodes.findIndex((n) => n.id === node.id);
      if (index > -1) {
        nodes.splice(index, 1);
      }
      this.logger.info(`Node disconnected: ${node.id}`);
    },
  },
  created() {
    this.logger.info("NodeMonitor service is created and ready to track node events.");
  },
};
