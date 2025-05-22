import { NotificationDomainService } from "../../domain/services/NotificationDomainService";
import { NotificationEntity } from "../../domain/entities/NotificationEntity";
import { TemplateEntity } from "../../domain/entities/TemplateEntity";
import { NotificationContent } from "../../domain/valueObjects/NotificationContent";
import type { IDomainEventPublisher } from "../../domain/events/DomainEventPublisher";
import { NotificationCreatedEvent, NotificationSentEvent, NotificationFailedEvent } from "../../domain/events/DomainEvent";
import { Criticality } from "../../models/notification";
import type { INotificationRepository } from "../../domain/repositories/INotificationRepository";
import type { ITemplateRepository } from "../../domain/repositories/ITemplateRepository";
import type { INotificationProvider } from "../../domain/ports/INotificationProvider";
import type { TemplateContext } from "../../models/template";

/**
 * Input data for sending a notification
 */
export interface SendNotificationInput {
  templateId: string;
  subscriberId?: string;
  topicId?: string;
  provider: "sms" | "push" | "email";
  payload: Record<string, any>;
  templateContext?: TemplateContext;
  criticality: Criticality;
}

/**
 * Result of sending a notification
 */
export interface SendNotificationResult {
  notification: NotificationEntity;
  success: boolean;
  error?: string;
}

/**
 * Configuration for the use case
 */
export interface SendNotificationConfig {
  providers: Record<string, INotificationProvider>;
  mediumRetryCount: number;
}

/**
 * Use case for sending a notification
 */
export class SendNotificationUseCase {
  constructor(
    private config: SendNotificationConfig,
    private notificationRepository: INotificationRepository,
    private templateRepository: ITemplateRepository,
    private domainService: NotificationDomainService,
    private eventPublisher: IDomainEventPublisher
  ) {}
  
  /**
   * Execute the use case
   */
  async execute(input: SendNotificationInput): Promise<SendNotificationResult> {
    try {
      // 1. Create notification entity
      const notification = this.domainService.createNotification({
        templateId: input.templateId,
        subscriberId: input.subscriberId,
        topicId: input.topicId,
        provider: input.provider,
        payload: input.payload,
        criticality: input.criticality
      });
      
      // 2. Save notification
      await this.notificationRepository.save(notification);
      
      // 3. Publish notification created event
      await this.eventPublisher.publish(new NotificationCreatedEvent(
        notification.id,
        notification.subscriberId,
        notification.topicId,
        notification.provider
      ));
      
      // 4. Apply template if context provided
      let processedNotification = notification;
      if (input.templateContext) {
        const template = await this.templateRepository.findById(input.templateId);
        if (template) {
          processedNotification = this.domainService.applyTemplate(
            notification,
            template,
            input.templateContext
          );
          await this.notificationRepository.update(processedNotification);
        }
      }
      
      // 5. Validate notification
      const validation = this.domainService.validateBeforeSending(processedNotification);
      if (!validation.isValid) {
        await this.handleFailure(processedNotification, `Validation failed: ${validation.errors.join(", ")}`);
        return {
          notification: processedNotification,
          success: false,
          error: validation.errors.join(", ")
        };
      }
      
      // 6. Send notification based on criticality
      await this.sendBasedOnCriticality(processedNotification);
      
      return {
        notification: processedNotification,
        success: true
      };
    } catch (error: any) {
      console.error("Error in SendNotificationUseCase:", error);
      return {
        notification: null as any,
        success: false,
        error: error.message
      };
    }
  }
  
  /**
   * Send notification based on its criticality
   */
  private async sendBasedOnCriticality(notification: NotificationEntity): Promise<void> {
    const provider = this.config.providers[notification.provider];
    if (!provider) {
      throw new Error(`Provider not found: ${notification.provider}`);
    }

    const criticality = notification.criticality;
    
    if (criticality === Criticality.Low) {
      // Fire-and-forget
      this.sendWithoutRetry(notification, provider).catch(error => {
        console.error("Error sending low criticality notification:", error);
      });
    } else if (criticality === Criticality.Medium) {
      // Medium criticality with retry
      for (let i = 0; i < this.config.mediumRetryCount; i++) {
        try { 
          await this.sendWithRetry(notification, provider); 
          break; 
        } catch (error) { 
          if (i === this.config.mediumRetryCount - 1) {
            const errorMessage = error instanceof Error ? error.message : String(error);
            await this.handleFailure(notification, errorMessage);
            throw new Error(`Failed to send medium criticality notification after ${this.config.mediumRetryCount} attempts: ${errorMessage}`); 
          }
        }
      }
    } else if (criticality === Criticality.High) {
      // High criticality with extended retry (would use more sophisticated retry logic in production)
      let retries = 0;
      const maxRetries = 10; // Higher number for critical notifications
      
      while (retries < maxRetries) {
        try {
          await this.sendWithRetry(notification, provider);
          break;
        } catch (error) {
          retries++;
          if (retries >= maxRetries) {
            const errorMessage = error instanceof Error ? error.message : String(error);
            await this.handleFailure(notification, errorMessage);
            throw new Error(`Failed to send high criticality notification after ${maxRetries} attempts: ${errorMessage}`);
          }
          
          // Exponential backoff
          const delay = Math.min(1000 * Math.pow(2, retries), 30000);
          await new Promise(resolve => setTimeout(resolve, delay));
        }
      }
    }
  }
  
  /**
   * Send notification without retry logic
   */
  private async sendWithoutRetry(notification: NotificationEntity, provider: INotificationProvider): Promise<void> {
    try {
      // Create content value object for the provider
      const content = new NotificationContent(notification.provider, notification.payload);
      
      // Send notification
      await provider.send(notification, content);
      
      notification.markAsSent();
      await this.notificationRepository.update(notification);
      
      // Publish sent event
      await this.eventPublisher.publish(new NotificationSentEvent(
        notification.id,
        notification.subscriberId,
        notification.provider
      ));
    } catch (err: any) {
      await this.handleFailure(notification, err.message);
      throw err;
    }
  }
  
  /**
   * Send notification with retry capability
   */
  private async sendWithRetry(notification: NotificationEntity, provider: INotificationProvider): Promise<void> {
    try {
      // Create content value object for the provider
      const content = new NotificationContent(notification.provider, notification.payload);
      
      // Send notification
      await provider.send(notification, content);
      
      notification.markAsSent();
      await this.notificationRepository.update(notification);
      
      // Publish sent event
      await this.eventPublisher.publish(new NotificationSentEvent(
        notification.id,
        notification.subscriberId,
        notification.provider
      ));
    } catch (err: any) {
      throw err;
    }
  }
  
  /**
   * Handle notification failure
   */
  private async handleFailure(notification: NotificationEntity, reason: string): Promise<void> {
    notification.markAsFailed();
    await this.notificationRepository.update(notification);
    
    // Publish failure event
    await this.eventPublisher.publish(new NotificationFailedEvent(
      notification.id,
      notification.subscriberId,
      notification.provider,
      reason
    ));
  }
}
