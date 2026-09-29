import express, { type ErrorRequestHandler, type Express } from "express";
import cors from "cors";
import { toNodeHandler } from "better-auth/node";
import { fileURLToPath } from "node:url";
import type { Db } from "mongodb";
import type { Auth } from "./auth.js";
import { createHealthRouter } from "./routes/health.js";
import { createMeRouter } from "./routes/me.js";

export function createApp({ auth, mongoDb }: { auth: Auth; mongoDb: Db }): Express {
  const app = express();

  app.use(cors({ origin: true, credentials: true }));

  // Better Auth must be mounted before express.json() so it can read the raw body.
  app.all("/api/auth/{*any}", toNodeHandler(auth));

  app.use(express.json());

  app.use("/health", createHealthRouter({ mongoDb }));
  app.use("/api/me", createMeRouter({ auth }));

  // Browser test page for the auth flows (public/index.html). Not served in production.
  if (process.env.NODE_ENV !== "production") {
    app.use(express.static(fileURLToPath(new URL("../public", import.meta.url))));
  }

  app.use((_req, res) => {
    res.status(404).json({ error: "Not found" });
  });

  const errorHandler: ErrorRequestHandler = (err, _req, res, _next) => {
    console.error(err);
    res.status(500).json({ error: "Internal server error" });
  };
  app.use(errorHandler);

  return app;
}
