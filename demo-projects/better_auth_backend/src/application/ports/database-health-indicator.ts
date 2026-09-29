export interface DatabaseHealthIndicator {
  isHealthy(): Promise<boolean>;
}
