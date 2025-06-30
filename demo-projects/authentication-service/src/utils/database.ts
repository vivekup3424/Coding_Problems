import { MongoClient, Db, Collection, Document } from 'mongodb';

export class DatabaseConnection {
  private client: MongoClient | null = null;
  private db: Db | null = null;

  async connect(): Promise<Db> {
    try {
      const uri = process.env.MONGODB_URI || "mongodb://localhost:27017";
      const dbName = process.env.DB_NAME || "home_automation_auth";
      
      this.client = new MongoClient(uri, {
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

  async disconnect(): Promise<void> {
    if (this.client) {
      await this.client.close();
      console.log("✅ Disconnected from MongoDB");
    }
  }

  getDatabase(): Db {
    if (!this.db) {
      throw new Error("Database not connected. Call connect() first.");
    }
    return this.db;
  }

  getCollection<T extends Document = Document>(name: string): Collection<T> {
    return this.getDatabase().collection<T>(name);
  }
}

export default new DatabaseConnection();
