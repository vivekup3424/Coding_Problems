const { Service } = require("moleculer");
const { MongoClient } = require("mongodb");

module.exports = {
  name: "cache",
  
  settings: {
    mongoUrl: process.env.MONGODB_URI || "mongodb://localhost:27017",
    dbName: process.env.DB_NAME || "home_automation_auth",
    collectionName: "cache",
    defaultTTL: 30 * 60 * 1000 // 30 minutes in milliseconds
  },

  actions: {
    /**
     * Set a cache entry
     */
    set: {
      params: {
        key: "string",
        value: "any",
        ttl: { type: "number", optional: true }
      },
      async handler(ctx) {
        const { key, value, ttl } = ctx.params;
        const expiresAt = new Date(Date.now() + (ttl || this.settings.defaultTTL));
        
        await this.collection.replaceOne(
          { key },
          {
            key,
            value,
            expiresAt,
            createdAt: new Date(),
            updatedAt: new Date()
          },
          { upsert: true }
        );
        
        return true;
      }
    },

    /**
     * Get a cache entry
     */
    get: {
      params: {
        key: "string"
      },
      async handler(ctx) {
        const { key } = ctx.params;
        
        const entry = await this.collection.findOne({
          key,
          expiresAt: { $gt: new Date() }
        });
        
        return entry ? entry.value : null;
      }
    },

    /**
     * Delete a cache entry
     */
    del: {
      params: {
        key: "string"
      },
      async handler(ctx) {
        const { key } = ctx.params;
        
        const result = await this.collection.deleteOne({ key });
        return result.deletedCount > 0;
      }
    },

    /**
     * Clear expired cache entries
     */
    cleanup: {
      async handler(ctx) {
        const result = await this.collection.deleteMany({
          expiresAt: { $lt: new Date() }
        });
        
        return {
          deletedCount: result.deletedCount,
          cleanupTime: new Date()
        };
      }
    },

    /**
     * Clear all cache entries
     */
    clear: {
      async handler(ctx) {
        const result = await this.collection.deleteMany({});
        return {
          deletedCount: result.deletedCount,
          clearTime: new Date()
        };
      }
    }
  },

  methods: {
    /**
     * Initialize MongoDB connection
     */
    async initMongo() {
      this.client = new MongoClient(this.settings.mongoUrl);
      await this.client.connect();
      this.db = this.client.db(this.settings.dbName);
      this.collection = this.db.collection(this.settings.collectionName);
      
      // Create TTL index for automatic cleanup
      await this.collection.createIndex(
        { expiresAt: 1 },
        { expireAfterSeconds: 0 }
      );
      
      // Create index on key for faster lookups
      await this.collection.createIndex({ key: 1 }, { unique: true });
      
      this.logger.info("MongoDB cache connection established");
    }
  },

  async started() {
    await this.initMongo();
    
    // Schedule periodic cleanup every 10 minutes
    this.cleanupTimer = setInterval(async () => {
      try {
        const result = await this.actions.cleanup();
        if (result.deletedCount > 0) {
          this.logger.info(`Cleaned up ${result.deletedCount} expired cache entries`);
        }
      } catch (error) {
        this.logger.error("Cache cleanup error:", error);
      }
    }, 10 * 60 * 1000);
  },

  async stopped() {
    if (this.cleanupTimer) {
      clearInterval(this.cleanupTimer);
    }
    
    if (this.client) {
      await this.client.close();
      this.logger.info("MongoDB cache connection closed");
    }
  }
};
