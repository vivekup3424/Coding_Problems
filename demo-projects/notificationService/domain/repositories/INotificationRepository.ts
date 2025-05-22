import type { Notification } from "../../models/notification";
import { NotificationEntity } from "../entities/NotificationEntity";

/**
 * Repository interface for Notification domain entity
 */
export interface INotificationRepository {
  /**
   * Save a notification entity
   */
  save(notification: NotificationEntity): Promise<void>;
  
  /**
   * Find a notification by ID
   */
  findById(id: string): Promise<NotificationEntity | null>;
  
  /**
   * Find all notifications by subscriber ID
   */
  findBySubscriberId(subscriberId: string): Promise<NotificationEntity[]>;
  
  /**
   * Find all notifications by topic ID
   */
  findByTopicId(topicId: string): Promise<NotificationEntity[]>;
  
  /**
   * Find all unread notifications for a subscriber
   */
  findUnreadBySubscriberId(subscriberId: string): Promise<NotificationEntity[]>;
  
  /**
   * Update a notification entity
   */
  update(notification: NotificationEntity): Promise<void>;
  
  /**
   * List all notifications with optional filtering
   */
  list(filter?: Partial<Notification>): Promise<NotificationEntity[]>;
}
