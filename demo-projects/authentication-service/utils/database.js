const { MongoClient } = require("mongodb");

class DatabaseConnection {
  constructor() {
    this.client = null;
    this.db = null;
  }

  async connect() {
    try {
      const uri = process.env.MONGODB_URI || "mongodb://localhost:27017";
      const dbName = process.env.DB_NAME || "home_automation_auth";
      
      this.client = new MongoClient(uri, {
        useUnifiedTopology: true,
        maxPoolSize: 10,
        serverSelectionTimeoutMS: 5000,
        socketTimeoutMS: 45000,
      });

      await this.client.connect();
      this.db = this.client.db(dbName);
      
      console.log("✅ Connected to MongoDB");
      return this.db;
    } catch (error) {
      console.error("❌ MongoDB connection error:", error);
      throw error;
    }
  }

  async disconnect() {
    if (this.client) {
      await this.client.close();
      console.log("✅ Disconnected from MongoDB");
    }
  }

  getDatabase() {
    if (!this.db) {
      throw new Error("Database not connected. Call connect() first.");
    }
    return this.db;
  }

  getCollection(name) {
    return this.getDatabase().collection(name);
  }
}

module.exports = new DatabaseConnection();
