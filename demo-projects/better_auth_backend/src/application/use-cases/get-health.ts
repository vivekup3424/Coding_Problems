import type { DatabaseHealthIndicator } from "../ports/database-health-indicator.js";

export interface HealthReport {
  status: "ok" | "degraded";
  uptime: number;
  database: "up" | "down";
}

export class GetHealth {
  private readonly databaseHealthIndicator: DatabaseHealthIndicator;

  constructor({
    databaseHealthIndicator,
  }: {
    databaseHealthIndicator: DatabaseHealthIndicator;
  }) {
    this.databaseHealthIndicator = databaseHealthIndicator;
  }

  async execute(): Promise<HealthReport> {
    const databaseUp = await this.databaseHealthIndicator.isHealthy();

    return {
      status: databaseUp ? "ok" : "degraded",
      uptime: process.uptime(),
      database: databaseUp ? "up" : "down",
    };
  }
}
