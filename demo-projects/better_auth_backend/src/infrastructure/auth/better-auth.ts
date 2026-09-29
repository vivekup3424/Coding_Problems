import { betterAuth } from "better-auth";
import { mongodbAdapter } from "better-auth/adapters/mongodb";
import { toNodeHandler } from "better-auth/node";
import type { Db, MongoClient } from "mongodb";
import type { Config } from "../config.js";

export function createAuth({
  config,
  mongoClient,
  mongoDb,
}: {
  config: Config;
  mongoClient: MongoClient;
  mongoDb: Db;
}) {
  return betterAuth({
    database: mongodbAdapter(mongoDb, {
      client: mongoClient,
      // Transactions need a replica set; the local docker-compose MongoDB is standalone.
      transaction: false,
    }),
    baseURL: config.betterAuthUrl,
    secret: config.betterAuthSecret,
    trustedOrigins: config.trustedOrigins,
    emailAndPassword: {
      enabled: true,
    },
  });
}

export type Auth = ReturnType<typeof createAuth>;

export type AuthHttpHandler = ReturnType<typeof toNodeHandler>;

export function createAuthHttpHandler({ auth }: { auth: Auth }): AuthHttpHandler {
  return toNodeHandler(auth);
}
