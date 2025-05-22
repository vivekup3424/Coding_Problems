import { NotificationContent } from "../valueObjects/NotificationContent";
import { NotificationEntity } from "../entities/NotificationEntity";

/**
 * Port interface for notification providers to implement
 * This is a hexagonal architecture port that allows the domain to communicate
 * with the external world without depending on concrete implementations
 */
export interface INotificationProvider {
  /**
   * Send a notification through this provider
   * @param notification The notification entity to send
   * @param content The provider-specific content to send
   */
  send(notification: NotificationEntity, content: NotificationContent): Promise<void>;
  
  /**
   * Get the channel type handled by this provider
   */
  getChannel(): string;
  
  /**
   * Validate if the provided content is valid for this provider
   */
  validateContent(content: NotificationContent): boolean;
}
