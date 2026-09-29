import type { Db } from "mongodb";
import type { DatabaseHealthIndicator } from "../../application/ports/database-health-indicator.js";

export class MongoHealthIndicator implements DatabaseHealthIndicator {
  private readonly mongoDb: Db;

  constructor({ mongoDb }: { mongoDb: Db }) {
    this.mongoDb = mongoDb;
  }

  async isHealthy(): Promise<boolean> {
    try {
      await this.mongoDb.command({ ping: 1 });
      return true;
    } catch {
      return false;
    }
  }
}
