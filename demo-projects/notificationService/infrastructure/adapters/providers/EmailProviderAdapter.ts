import nodemailer from "nodemailer";
import type { INotificationProvider } from "../../../domain/ports/INotificationProvider";
import { NotificationEntity } from "../../../domain/entities/NotificationEntity";
import { NotificationContent } from "../../../domain/valueObjects/NotificationContent";

export interface EmailConfig {
  transportOptions: any;
}

/**
 * Adapter for sending email notifications
 */
export class EmailProviderAdapter implements INotificationProvider {
  private transporter: any;
  private readonly channel = "email";

  constructor(private config: EmailConfig) {
    this.transporter = nodemailer.createTransport(this.config.transportOptions);
  }

  /**
   * Get the channel type for this provider
   */
  getChannel(): string {
    return this.channel;
  }

  /**
   * Validate if the content is valid for email
   */
  validateContent(content: NotificationContent): boolean {
    console.log(
      "[EmailProviderAdapter] Validating content.payload:",
      JSON.stringify(content.getPayload())
    ); // Changed to getPayload()
    const payload = content.getPayload(); // Changed to getPayload()
    return (
      typeof payload.to === "string" &&
      payload.to.length > 0 &&
      typeof payload.subject === "string" &&
      (typeof payload.body === "string" || typeof payload.html === "string")
    );
  }

  /**
   * Send an email notification
   */
  async send(
    notification: NotificationEntity,
    content: NotificationContent
  ): Promise<void> {
    if (!this.validateContent(content)) {
      throw new Error("Invalid email content format");
    }

    const payload = content.getPayload();

    // Simulate sending email
    console.log(
      `[EmailProviderAdapter] Simulating email send to: ${payload.to} with subject: ${payload.subject}`
    );
    // await this.transporter.sendMail({
    //   to: payload.to,
    //   subject: payload.subject,
    //   text: payload.body,
    //   html: payload.html || undefined,
    // });

    console.log(`EmailProvider: notification sent id=${notification.id}`);
  }
}
