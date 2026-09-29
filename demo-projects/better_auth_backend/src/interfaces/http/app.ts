import express, { type Express, type RequestHandler } from "express";
import cors from "cors";
import type { HealthController } from "./controllers/health.controller.js";
import type { MeController } from "./controllers/me.controller.js";
import { errorHandler, notFoundHandler } from "./middleware/error-handlers.js";

export function createHttpApp({
  authHttpHandler,
  healthController,
  meController,
}: {
  authHttpHandler: RequestHandler;
  healthController: HealthController;
  meController: MeController;
}): Express {
  const app = express();

  app.use(cors({ origin: true, credentials: true }));

  // The auth handler must be mounted before express.json() so it can read the raw body.
  app.all("/api/auth/{*any}", authHttpHandler);

  app.use(express.json());

  app.get("/health", healthController.show);
  app.get("/api/me", meController.show);

  app.use(notFoundHandler);
  app.use(errorHandler);

  return app;
}
