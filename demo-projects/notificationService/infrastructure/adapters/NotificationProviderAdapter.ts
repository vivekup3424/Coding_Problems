import type { NotificationEntity } from "../../domain/entities/NotificationEntity";
import type { INotificationProvider } from "../../domain/ports/INotificationProvider";
import type { Notification } from "../../models/notification";
import { NotificationContent } from "../../domain/valueObjects/NotificationContent";

/**
 * Adapter that bridges between application layer and notification providers
 * This follows the Adapter pattern from Clean Architecture
 */
export class NotificationProviderAdapter implements INotificationProvider {
  constructor(private provider: INotificationProvider) {}

  /**
   * Send a notification using the provider
   */
  async send(notification: NotificationEntity, content: NotificationContent): Promise<void> {
    // Send using domain provider
    await this.provider.send(notification, content);
  }

  /**
   * Get the channel type handled by this provider
   */
  getChannel(): string {
    return this.provider.getChannel();
  }
  
  /**
   * Validate if the provided content is valid for this provider
   */
  validateContent(content: NotificationContent): boolean {
    return this.provider.validateContent(content);
  }
}
