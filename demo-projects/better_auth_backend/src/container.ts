import { asClass, asFunction, asValue, createContainer, InjectionMode } from "awilix";
import type { Express } from "express";
import type { Db, MongoClient } from "mongodb";
import type { DatabaseHealthIndicator } from "./application/ports/database-health-indicator.js";
import type { SessionProvider } from "./application/ports/session-provider.js";
import { GetCurrentSession } from "./application/use-cases/get-current-session.js";
import { GetHealth } from "./application/use-cases/get-health.js";
import {
  createAuth,
  createAuthHttpHandler,
  type Auth,
  type AuthHttpHandler,
} from "./infrastructure/auth/better-auth.js";
import { BetterAuthSessionProvider } from "./infrastructure/auth/better-auth-session-provider.js";
import { config, type Config } from "./infrastructure/config.js";
import { createMongoClient, createMongoDb } from "./infrastructure/database/mongo.js";
import { MongoHealthIndicator } from "./infrastructure/database/mongo-health-indicator.js";
import { HealthController } from "./interfaces/http/controllers/health.controller.js";
import { MeController } from "./interfaces/http/controllers/me.controller.js";
import { createHttpApp } from "./interfaces/http/app.js";

export interface Cradle {
  config: Config;
  mongoClient: MongoClient;
  mongoDb: Db;
  auth: Auth;
  authHttpHandler: AuthHttpHandler;
  sessionProvider: SessionProvider;
  databaseHealthIndicator: DatabaseHealthIndicator;
  getCurrentSession: GetCurrentSession;
  getHealth: GetHealth;
  healthController: HealthController;
  meController: MeController;
  httpApp: Express;
}

export function buildContainer() {
  const container = createContainer<Cradle>({
    injectionMode: InjectionMode.PROXY,
    strict: true,
  });

  container.register({
    // infrastructure
    config: asValue(config),
    mongoClient: asFunction(createMongoClient)
      .singleton()
      .disposer((client) => client.close()),
    mongoDb: asFunction(createMongoDb).singleton(),
    auth: asFunction(createAuth).singleton(),
    authHttpHandler: asFunction(createAuthHttpHandler).singleton(),
    sessionProvider: asClass(BetterAuthSessionProvider).singleton(),
    databaseHealthIndicator: asClass(MongoHealthIndicator).singleton(),

    // application
    getCurrentSession: asClass(GetCurrentSession).singleton(),
    getHealth: asClass(GetHealth).singleton(),

    // interfaces
    healthController: asClass(HealthController).singleton(),
    meController: asClass(MeController).singleton(),
    httpApp: asFunction(createHttpApp).singleton(),
  });

  return container;
}
