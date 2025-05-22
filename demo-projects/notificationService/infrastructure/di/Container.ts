import type { SubscriberApplicationService } from "../../application/services/SubscriberApplicationService";
import type { TopicApplicationService } from "../../application/services/TopicApplicationService";
import type { NotificationApplicationService } from "../../application/services/NotificationApplicationService";
import type { INotificationProvider } from "../../domain/ports/INotificationProvider";

/**
 * Simple dependency injection container
 */
export class Container {
  private instances = new Map<string, any>();

  /**
   * Register a singleton instance in the container
   */
  register<T>(key: string, instance: T): void {
    this.instances.set(key, instance);
  }

  /**
   * Get an instance from the container
   */
  get<T>(key: string): T {
    const instance = this.instances.get(key);
    if (!instance) {
      throw new Error(`No instance registered for key: ${key}`);
    }
    return instance as T;
  }
}

/**
 * Service locator for accessing services from the container
 */
export class ServiceLocator {
  constructor(private container: Container) {}

  getSubscriberApplicationService(): SubscriberApplicationService {
    return this.container.get<SubscriberApplicationService>("subscriberApplicationService");
  }

  getTopicApplicationService(): TopicApplicationService {
    return this.container.get<TopicApplicationService>("topicApplicationService");
  }

  getNotificationApplicationService(): NotificationApplicationService {
    return this.container.get<NotificationApplicationService>("notificationApplicationService");
  }

  getNotificationProvider(type: "sms" | "push" | "email"): INotificationProvider {
    return this.container.get<INotificationProvider>(`provider.${type}`);
  }
}

/**
 * Create and configure a container with all services
 */
export function createContainer(): Container {
  const container = new Container();
  return container;
}
