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
    console.log(
      "[PushProviderAdapter] Validating content.payload:",
      JSON.stringify(content.getPayload())
    ); // Changed to getPayload()
    const payload = content.getPayload(); // Changed to getPayload()
    return (
      typeof payload.token === "string" &&
      payload.token.length > 0 &&
      typeof payload.title === "string" &&
      typeof payload.body === "string"
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
    console.log(`[PushProviderAdapter] Simulating send for token: ${payload.token}`);
    console.log(`[PushProviderAdapter] Title: ${payload.title}, Body: ${payload.body}`);

    // Simulate a successful send without actual Firebase connection
    // In a real scenario, this would be:
    // const message = {
    //   token: payload.token,
    //   notification: {
    //     title: payload.title,
    //     body: payload.body,
    //   },
    //   // You can add more FCM options here, like `data` for custom payloads
    // };
    // try {
    //   const response = await this.app.messaging().send(message);
    //   console.log("[PushProviderAdapter] Successfully sent message:", response);
    // } catch (error) {
    //   console.error("[PushProviderAdapter] Error sending message:", error);
    //   throw new Error(`Failed to send push notification: ${error}`);
    // }
    return Promise.resolve(); // Simulate success
  }
}
