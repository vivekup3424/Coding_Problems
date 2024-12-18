const fs = require("fs").promises;
const path = require("path");

const INVENTORY_FILE = path.join(__dirname, "inventory.json");

module.exports = {
  name: "inventory",

  actions: {
    async addItem(ctx) {
      const { item, quantity } = ctx.params;
      const inventory = await this.loadInventory();
      if (inventory[item]) {
        inventory[item] += quantity;
      } else {
        // Add new item,if it doesn't exist
        inventory[item] = quantity;
      }
      await this.saveInventory(inventory);
      ctx.broadcast("inventory.updated", { item, quantity: inventory[item] });
      return `Item '${item}' updated. New quantity: ${inventory[item]}`;
    },

    async getItem(ctx) {
      const { item } = ctx.params;
      const inventory = await this.loadInventory();
      if (inventory[item]) {
        return { item, quantity: inventory[item] };
      } else {
        throw new Error(`Item '${item}' not found in inventory.`);
      }
    },

    async getAllItems() {
      const inventory = await this.loadInventory();
      return inventory;
    },
  },

  methods: {
    async loadInventory() {
      try {
        const data = await fs.readFile(INVENTORY_FILE, "utf-8");
        return JSON.parse(data);
      } catch (err) {
        if (err.code === "ENOENT") {
          return {};
        }
        throw err;
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
