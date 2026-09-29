import { MongoClient, type Db } from "mongodb";
import type { Config } from "../config.js";

export function createMongoClient({ config }: { config: Config }): MongoClient {
  return new MongoClient(config.mongodbUri);
}

// Uses the database named in the connection string.
export function createMongoDb({ mongoClient }: { mongoClient: MongoClient }): Db {
  return mongoClient.db();
}
