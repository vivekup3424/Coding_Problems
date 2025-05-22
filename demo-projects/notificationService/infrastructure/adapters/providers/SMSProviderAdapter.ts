import type { INotificationProvider } from "../../../domain/ports/INotificationProvider";
import { NotificationEntity } from "../../../domain/entities/NotificationEntity";
import { NotificationContent } from "../../../domain/valueObjects/NotificationContent";

export interface SMSConfig {
  accessToken: string;
  apiUrl?: string;
}

/**
 * Adapter for sending SMS notifications
 */
export class SMSProviderAdapter implements INotificationProvider {
  private readonly channel = "sms";

  constructor(private config: SMSConfig) {}

  /**
   * Get the channel type for this provider
   */
  getChannel(): string {
    return this.channel;
  }

  /**
   * Validate if the content is valid for SMS
   */
  validateContent(content: NotificationContent): boolean {
    const payload = content.getPayload();
    return Boolean(
      payload && 
      typeof payload.to === "string" && 
      typeof payload.message === "string"
    );
  }

  /**
   * Send an SMS notification
   */
  async send(notification: NotificationEntity, content: NotificationContent): Promise<void> {
    if (!this.validateContent(content)) {
      throw new Error("Invalid SMS content format");
    }

    const payload = content.getPayload();
    
    // TODO: integrate with actual SMS API using this.config.accessToken
    console.log(
      `SMSProvider: sending SMS to ${payload.to} with content: ${payload.message}`
    );
  }
}
