import type { Request, Response } from "express";
import type { GetHealth } from "../../../application/use-cases/get-health.js";

export class HealthController {
  private readonly getHealth: GetHealth;

  constructor({ getHealth }: { getHealth: GetHealth }) {
    this.getHealth = getHealth;
  }

  show = async (_req: Request, res: Response) => {
    const report = await this.getHealth.execute();
    res.status(report.status === "ok" ? 200 : 503).json(report);
  };
}
