const pino = require("pino")
module.exports = {
  name: "inventoryMonitor",

  events: {
    "inventory.updated"(data) {
      pino().info(`Inventory updated. Item: ${data.item}, New Quantity: ${data.quantity}`);
    },
  },
};
