const fs = require("fs").promises;
const path = require("path");

const INVENTORY_FILE = path.join(__dirname, "inventory.json");

module.exports = {
  name: "library",

  actions: {
    async updateItem(ctx) {
      const { item, quantity } = ctx.params;
      const inventory = await this.loadInventory();
      inventory[item] = quantity;
      await this.saveInventory(inventory);
      ctx.broadcast("inventory.updated", { item, quantity: inventory[item] });
      return `Item '${item}' updated. New quantity: ${inventory[item]}`;
    },
  },

  methods: {
    async loadInventory() {
      try {
        const data = await fs.readFile(INVENTORY_FILE, "utf-8");
        return JSON.parse(data);
      } catch (err) {
        if (err.code === "ENOENT") {
          return {}; // Return an empty object if the file doesn't exist
        }
        throw err; // Throw error if it's another issue
      }
    },

    async saveInventory(inventory) {
      await fs.writeFile(INVENTORY_FILE, JSON.stringify(inventory, null, 2), "utf-8");
    },
  },

  events: {
    "inventory.updated"(data) {
      console.log(`Inventory updated: ${data.item}, New Quantity: ${data.quantity}`);
    },
  },
};
