import type { INotificationRepository } from "../../domain/repositories/INotificationRepository";
import { NotificationEntity } from "../../domain/entities/NotificationEntity";
import { NotificationStatus } from "../../models/notification";
import { NotificationModel } from "../database/schemas/NotificationSchema";

/**
 * MongoDB implementation of the notification repository
 */
export class MongoNotificationRepository implements INotificationRepository {
  
  /**
   * Save a notification entity to MongoDB
   */
  async save(notification: NotificationEntity): Promise<void> {
    const data = notification.toJSON();
    
    // Use findOneAndUpdate with upsert to handle both inserts and updates
    await NotificationModel.findOneAndUpdate(
      { id: notification.id },
      data,
      { upsert: true, new: true }
    );
  }
  
  /**
   * Find a notification by ID from MongoDB
   */
  async findById(id: string): Promise<NotificationEntity | null> {
    const notification = await NotificationModel.findOne({ id }).lean();
    return notification ? NotificationEntity.fromJSON(notification) : null;
  }
  
  /**
   * Find all notifications by subscriber ID from MongoDB
   */
  async findBySubscriberId(subscriberId: string): Promise<NotificationEntity[]> {
    const notifications = await NotificationModel.find({ subscriberId }).lean();
    return notifications.map(data => NotificationEntity.fromJSON(data));
  }
  
  /**
   * Find all notifications by topic ID from MongoDB
   */
  async findByTopicId(topicId: string): Promise<NotificationEntity[]> {
    const notifications = await NotificationModel.find({ topicId }).lean();
    return notifications.map(data => NotificationEntity.fromJSON(data));
  }
  
  /**
   * Find all unread notifications for a subscriber from MongoDB
   */
  async findUnreadBySubscriberId(subscriberId: string): Promise<NotificationEntity[]> {
    const notifications = await NotificationModel.find({ 
      subscriberId, 
      readAt: { $exists: false } 
    }).lean();
    
    return notifications.map(data => NotificationEntity.fromJSON(data));
  }
  
  /**
   * Mark notification as read
   */
  async markAsRead(id: string): Promise<void> {
    await NotificationModel.findOneAndUpdate(
      { id },
      { 
        readAt: new Date(),
        status: 'READ'
      }
    );
  }
  
  /**
   * Delete notification by ID
   */
  async deleteById(id: string): Promise<void> {
    await NotificationModel.deleteOne({ id });
  }
}
