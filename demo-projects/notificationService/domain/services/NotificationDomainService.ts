import { NotificationEntity } from "../entities/NotificationEntity";
import { TemplateEntity } from "../entities/TemplateEntity";
import type { TemplateContext } from "../../models/template";
import { NotificationContent } from "../valueObjects/NotificationContent";
import { Criticality } from "../../models/notification";
import { v4 as uuidv4 } from "uuid";

/**
 * Domain service for notification business logic
 */
export class NotificationDomainService {
  /**
   * Create a new notification entity
   */
  createNotification(params: {
    templateId: string;
    subscriberId?: string;
    topicId?: string;
    provider: "sms" | "push" | "email";
    payload: Record<string, any>;
    criticality: Criticality;
  }): NotificationEntity {
    if (!params.subscriberId && !params.topicId) {
      throw new Error("Either subscriberId or topicId must be provided");
    }

    return new NotificationEntity({
      id: uuidv4(),
      templateId: params.templateId,
      subscriberId: params.subscriberId,
      topicId: params.topicId,
      provider: params.provider,
      payload: params.payload,
      criticality: params.criticality
    });
  }
  
  /**
   * Apply template rendering to notification
   */
  applyTemplate(
    notification: NotificationEntity,
    template: TemplateEntity,
    context: TemplateContext
  ): NotificationEntity {
    try {
      const renderedContent = template.render(context);
      let payload = { ...notification.payload };
      
      // Create content with rendered message
      const notificationContent = new NotificationContent(
        notification.provider, 
        payload
      ).withMessage(renderedContent);
      
      // Create a new notification with updated payload
      return new NotificationEntity({
        id: notification.id,
        templateId: notification.templateId,
        subscriberId: notification.subscriberId,
        topicId: notification.topicId,
        provider: notification.provider,
        payload: notificationContent.data,
        status: notification.status,
        criticality: notification.criticality,
        createdAt: notification.createdAt,
        updatedAt: new Date()
      });
    } catch (error: any) {
      console.error(`Template rendering error: ${error.message || error}`);
      return notification;
    }
  }
  
  /**
   * Validate notification before sending
   */
  validateBeforeSending(notification: NotificationEntity): { isValid: boolean; errors: string[] } {
    const errors: string[] = [];
    
    // Check if notification has required provider-specific fields
    try {
      new NotificationContent(notification.provider, notification.payload);
    } catch (error: any) {
      errors.push(error.message);
    }
    
    // Check that either subscriberId or topicId is set
    if (!notification.subscriberId && !notification.topicId) {
      errors.push("Either subscriberId or topicId must be provided");
    }
    
    return {
      isValid: errors.length === 0,
      errors
    };
  }
  
  /**
   * Check if notification needs a delivery retry based on criticality
   */
  shouldRetry(notification: NotificationEntity, attemptCount: number): boolean {
    if (notification.criticality === Criticality.Low) {
      return false; // No retries for low criticality
    }
    
    if (notification.criticality === Criticality.Medium) {
      // For medium criticality, retry up to a limit
      // Actual limit comes from configuration in application service
      return true;
    }
    
    if (notification.criticality === Criticality.High) {
      // For high criticality, always retry
      return true;
    }
    
    return false;
  }
}
