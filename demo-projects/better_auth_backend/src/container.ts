import { asClass, asFunction, asValue, createContainer, InjectionMode } from "awilix";
import type { Express } from "express";
import type { Db, MongoClient } from "mongodb";
import { createApp } from "./app.js";
import { createAuth, type Auth } from "./auth.js";
import { config, type Config } from "./config.js";
import { createMongoClient, createMongoDb } from "./db.js";
import { ConsoleSmsSender, type SmsSender } from "./sms.js";

export interface Cradle {
  config: Config;
  mongoClient: MongoClient;
  mongoDb: Db;
  smsSender: SmsSender;
  auth: Auth;
  app: Express;
}

export function buildContainer() {
  const container = createContainer<Cradle>({
    injectionMode: InjectionMode.PROXY,
    strict: true,
  });

  container.register({
    config: asValue(config),
    mongoClient: asFunction(createMongoClient)
      .singleton()
      .disposer((client) => client.close()),
    mongoDb: asFunction(createMongoDb).singleton(),
    smsSender: asClass(ConsoleSmsSender).singleton(),
    auth: asFunction(createAuth).singleton(),
    app: asFunction(createApp).singleton(),
  });

  return container;
}
