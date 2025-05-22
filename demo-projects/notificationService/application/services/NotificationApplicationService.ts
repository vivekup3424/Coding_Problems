import { SendNotificationUseCase } from '../useCases/SendNotificationUseCase';
import type { 
  SendNotificationInput, 
  SendNotificationResult 
} from '../useCases/SendNotificationUseCase';
import { MarkNotificationAsReadUseCase } from '../useCases/MarkNotificationAsReadUseCase';
import type { 
  MarkNotificationAsReadInput,
  MarkNotificationAsReadResult 
} from '../useCases/MarkNotificationAsReadUseCase';
import type { NotificationEntity } from '../../domain/entities/NotificationEntity';
import type { INotificationRepository } from '../../domain/repositories/INotificationRepository';
import type { ITemplateRepository } from '../../domain/repositories/ITemplateRepository';
import { Criticality } from "../../models/notification";
import type { TemplateContext } from "../../models/template";

export interface CreateNotificationOptions {
  templateId: string;
  subscriberId?: string;
  topicId?: string;
  provider: "sms" | "push" | "email";
  payload: Record<string, any>;
  templateContext?: TemplateContext;
  criticality: Criticality;
}

export class NotificationApplicationService {
  constructor(
    private sendNotificationUseCase: SendNotificationUseCase,
    private markAsReadUseCase: MarkNotificationAsReadUseCase,
    private notificationRepository: INotificationRepository,
    private templateRepository: ITemplateRepository
  ) {}

  /**
   * Send a notification
   */
  async sendNotification(input: SendNotificationInput): Promise<SendNotificationResult> {
    return this.sendNotificationUseCase.execute(input);
  }

  /**
   * Mark a notification as read
   */
  async markNotificationAsRead(
    notificationId: string, 
    clientData?: Record<string, any>
  ): Promise<MarkNotificationAsReadResult> {
    return this.markAsReadUseCase.execute({
      notificationId,
      clientData
    });
  }

  /**
   * Get a notification by ID
   */
  async getNotificationById(id: string): Promise<NotificationEntity | null> {
    return this.notificationRepository.findById(id);
  }

  /**
   * Get all notifications for a subscriber
   */
  async getNotificationsForSubscriber(subscriberId: string): Promise<NotificationEntity[]> {
    return this.notificationRepository.findBySubscriberId(subscriberId);
  }

  /**
   * Get unread notifications for a subscriber
   */
  async getUnreadNotificationsForSubscriber(subscriberId: string): Promise<NotificationEntity[]> {
    return this.notificationRepository.findUnreadBySubscriberId(subscriberId);
  }

  /**
   * Create and send a notification in one operation
   * This is a convenience method that combines multiple use cases
   */
  async createAndSendNotification(
    options: CreateNotificationOptions, 
    subscriberIds: string[]
  ): Promise<NotificationEntity[]> {
    const results: NotificationEntity[] = [];
    
    // If subscriberIds are provided, send to each subscriber
    const targets = subscriberIds || (options.subscriberId ? [options.subscriberId] : []);
    
    for (const subscriberId of targets) {
      const input: SendNotificationInput = {
        templateId: options.templateId,
        subscriberId: subscriberId,
        topicId: options.topicId,
        provider: options.provider,
        payload: options.payload,
        templateContext: options.templateContext,
        criticality: options.criticality
      };
      
      const result = await this.sendNotificationUseCase.execute(input);
      
      if (result.success && result.notification) {
        results.push(result.notification);
      }
    }
    
    return results;
  }
  
  /**
   * Mark a notification as acknowledged
   */
  async acknowledgeNotification(notificationId: string): Promise<boolean> {
    const notification = await this.notificationRepository.findById(notificationId);
    if (!notification) return false;
    
    notification.acknowledge();
    await this.notificationRepository.update(notification);
    return true;
  }
}
