import type { IDomainEventPublisher } from "../../domain/events/DomainEventPublisher";
import { NotificationReadEvent } from "../../domain/events/DomainEvent";
import type { INotificationRepository } from "../../domain/repositories/INotificationRepository";

/**
 * Input for marking a notification as read
 */
export interface MarkNotificationAsReadInput {
  notificationId: string;
  clientData?: {
    deviceId?: string;
    clientTimestamp?: number;
    [key: string]: any;
  };
}

/**
 * Result of marking a notification as read
 */
export interface MarkNotificationAsReadResult {
  success: boolean;
  error?: string;
}

/**
 * Use case for marking a notification as read
 */
export class MarkNotificationAsReadUseCase {
  constructor(
    private notificationRepository: INotificationRepository,
    private eventPublisher: IDomainEventPublisher
  ) {}
  
  /**
   * Execute the use case
   */
  async execute(input: MarkNotificationAsReadInput): Promise<MarkNotificationAsReadResult> {
    try {
      const notification = await this.notificationRepository.findById(input.notificationId);
      
      if (!notification) {
        return {
          success: false,
          error: `Notification with id ${input.notificationId} not found`
        };
      }
      
      // Mark the notification as read
      notification.markAsRead(input.clientData);
      
      // Update the repository
      await this.notificationRepository.update(notification);
      
      // Publish read event
      await this.eventPublisher.publish(new NotificationReadEvent(
        notification.id,
        notification.subscriberId,
        input.clientData?.deviceId,
        notification.readAt as Date
      ));
      
      return { success: true };
    } catch (error: any) {
      console.error("Error in MarkNotificationAsReadUseCase:", error);
      return {
        success: false,
        error: error.message
      };
    }
  }
}
