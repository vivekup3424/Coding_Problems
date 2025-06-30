import { Service, ServiceBroker } from "moleculer";
import { MongoClient, Db, Collection } from "mongodb";
import { CacheEntry } from "../types";

interface CacheServiceSettings {
  mongoUrl: string;
  dbName: string;
  collectionName: string;
  defaultTTL: number;
}

interface CacheServiceSchema {
  name: string;
  settings: CacheServiceSettings;
  actions: {
    set: {
      params: {
        key: string;
        value: any;
        ttl?: number;
      };
      handler: (ctx: any) => Promise<boolean>;
    };
    get: {
      params: {
        key: string;
      };
      handler: (ctx: any) => Promise<any>;
    };
    del: {
      params: {
        key: string;
      };
      handler: (ctx: any) => Promise<boolean>;
    };
    cleanup: {
      handler: (ctx: any) => Promise<{ deletedCount: number; cleanupTime: Date }>;
    };
    clear: {
      handler: (ctx: any) => Promise<{ deletedCount: number; clearTime: Date }>;
    };
  };
  methods: {
    initMongo: () => Promise<void>;
  };
  started: () => Promise<void>;
  stopped: () => Promise<void>;
}

export class CacheService extends Service {
  private client!: MongoClient;
  private db!: Db;
  private collection!: Collection<CacheEntry>;
  private cleanupTimer?: NodeJS.Timeout;

  constructor(broker: ServiceBroker) {
    super(broker);

    this.parseServiceSchema({
      name: "cache",
      
      settings: {
        mongoUrl: process.env.MONGODB_URI || "mongodb://localhost:27017",
        dbName: process.env.DB_NAME || "home_automation_auth",
        collectionName: "cache",
        defaultTTL: 30 * 60 * 1000 // 30 minutes in milliseconds
      } as CacheServiceSettings,

      actions: {
        set: {
          params: {
            key: "string",
            value: "any",
            ttl: { type: "number", optional: true }
          },
          handler: async (ctx) => {
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

        get: {
          params: {
            key: "string"
          },
          handler: async (ctx) => {
            const { key } = ctx.params;
            
            const entry = await this.collection.findOne({
              key,
              expiresAt: { $gt: new Date() }
            });
            
            return entry ? entry.value : null;
          }
        },

        del: {
          params: {
            key: "string"
          },
          handler: async (ctx) => {
            const { key } = ctx.params;
            
            const result = await this.collection.deleteOne({ key });
            return result.deletedCount > 0;
          }
        },

        cleanup: {
          handler: async (ctx) => {
            const result = await this.collection.deleteMany({
              expiresAt: { $lt: new Date() }
            });
            
            return {
              deletedCount: result.deletedCount,
              cleanupTime: new Date()
            };
          }
        },

        clear: {
          handler: async (ctx) => {
            const result = await this.collection.deleteMany({});
            return {
              deletedCount: result.deletedCount,
              clearTime: new Date()
            };
          }
        }
      },

      methods: {
        initMongo: async () => {
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

      started: async () => {
        await this.schema.methods.initMongo.call(this);
        
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

      stopped: async () => {
        if (this.cleanupTimer) {
          clearInterval(this.cleanupTimer);
        }
        
        if (this.client) {
          await this.client.close();
          this.logger.info("MongoDB cache connection closed");
        }
      }
    });
  }
}

export default CacheService;
