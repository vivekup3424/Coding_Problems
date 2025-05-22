import type { INotificationProvider } from "../../../domain/ports/INotificationProvider";

/**
 * Registry for notification providers
 * Acts as a factory for retrieving providers by channel
 */
export class ProviderRegistry {
  private providers: Map<string, INotificationProvider> = new Map();

  /**
   * Register a notification provider
   */
  registerProvider(provider: INotificationProvider): void {
    const channel = provider.getChannel();
    if (this.providers.has(channel)) {
      console.warn(`Provider for channel '${channel}' is being overwritten`);
    }
    this.providers.set(channel, provider);
  }

  /**
   * Get a notification provider by channel
   */
  getProvider(channel: string): INotificationProvider | undefined {
    return this.providers.get(channel);
  }

  /**
   * Check if a provider exists for a channel
   */
  hasProvider(channel: string): boolean {
    return this.providers.has(channel);
  }

  /**
   * Get all registered providers
   */
  getAllProviders(): INotificationProvider[] {
    return Array.from(this.providers.values());
  }

  /**
   * Get all registered provider channels
   */
  getAvailableChannels(): string[] {
    return Array.from(this.providers.keys());
  }
}
