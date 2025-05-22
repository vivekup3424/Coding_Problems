import admin from "firebase-admin";
import type { INotificationProvider } from "../../../domain/ports/INotificationProvider";
import { NotificationEntity } from "../../../domain/entities/NotificationEntity";
import { NotificationContent } from "../../../domain/valueObjects/NotificationContent";

export interface PushConfig {
  firebaseConfig: Record<string, any>;
  appName?: string;
}

/**
 * Adapter for sending push notifications using Firebase
 */
export class PushProviderAdapter implements INotificationProvider {
  private app: any;
  private readonly channel = "push";

  constructor(private config: PushConfig) {
    const appName = config.appName || "push-provider";
    this.app = admin.initializeApp(config.firebaseConfig, appName);
  }

  /**
   * Get the channel type for this provider
   */
  getChannel(): string {
    return this.channel;
  }

  /**
   * Validate if the content is valid for push notifications
   */
  validateContent(content: NotificationContent): boolean {
    const payload = content.getPayload();
    return Boolean(
      payload && 
      typeof payload.token === "string" && 
      typeof payload.title === "string" && 
      payload.body !== undefined
    );
  }

  /**
   * Send a push notification
   */
  async send(notification: NotificationEntity, content: NotificationContent): Promise<void> {
    if (!this.validateContent(content)) {
      throw new Error("Invalid push notification content format");
    }

    const payload = content.getPayload();
    
    const message: any = {
      token: payload.token,
      notification: {
        title: payload.title,
        body: payload.body,
      },
      data: payload.data || {}
    };
    
    await this.app.messaging().send(message);
    console.log(`PushProvider: notification sent id=${notification.id}`);
  }
}
