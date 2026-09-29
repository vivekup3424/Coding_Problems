import { Router } from "express";
import type { Db } from "mongodb";

export function createHealthRouter({ mongoDb }: { mongoDb: Db }): Router {
  const router = Router();

  router.get("/", async (_req, res) => {
    const databaseUp = await mongoDb
      .command({ ping: 1 })
      .then(() => true)
      .catch(() => false);

    res.status(databaseUp ? 200 : 503).json({
      status: databaseUp ? "ok" : "degraded",
      uptime: process.uptime(),
      database: databaseUp ? "up" : "down",
    });
  });

  return router;
}
