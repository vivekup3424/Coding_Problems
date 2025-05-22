import type { Notification } from "../../models/notification";
import type { INotificationRepository } from "../../domain/repositories/INotificationRepository";
import { NotificationStatus } from "../../models/notification";
import { NotificationEntity } from "../../domain/entities/NotificationEntity";
import { BloomFilter } from "../../utils/BloomFilter";

/**
 * In-memory implementation of the notification repository
 */
export class InMemoryNotificationRepository implements INotificationRepository {
  private notifications = new Map<string, Record<string, any>>();
  private bloomFilter = new BloomFilter();
  
  async save(notification: NotificationEntity): Promise<void> {
    const data = notification.toJSON();
    this.notifications.set(notification.id, data);
    this.bloomFilter.add(notification.id);
  }
  
  async findById(id: string): Promise<NotificationEntity | null> {
    if (!this.bloomFilter.has(id)) return null;
    const data = this.notifications.get(id);
    return data ? NotificationEntity.fromJSON(data) : null;
  }
  
  async findBySubscriberId(subscriberId: string): Promise<NotificationEntity[]> {
    return Array.from(this.notifications.values())
      .filter(n => n.subscriberId === subscriberId)
      .map(data => NotificationEntity.fromJSON(data));
  }
  
  async findByTopicId(topicId: string): Promise<NotificationEntity[]> {
    return Array.from(this.notifications.values())
      .filter(n => n.topicId === topicId)
      .map(data => NotificationEntity.fromJSON(data));
  }
  
  async findUnreadBySubscriberId(subscriberId: string): Promise<NotificationEntity[]> {
    return Array.from(this.notifications.values())
      .filter(n => n.subscriberId === subscriberId && n.status !== NotificationStatus.Read)
      .map(data => NotificationEntity.fromJSON(data));
  }
  
  async update(notification: NotificationEntity): Promise<void> {
    const data = notification.toJSON();
    this.notifications.set(notification.id, data);
  }
  
  async list(filter?: Partial<Notification>): Promise<NotificationEntity[]> {
    let result = Array.from(this.notifications.values());
    
    if (filter) {
      result = result.filter(data => {
        for (const [key, value] of Object.entries(filter)) {
          if (data[key] !== value) {
            return false;
          }
        }
        return true;
      });
    }
    
    return result.map(data => NotificationEntity.fromJSON(data));
  }
}
