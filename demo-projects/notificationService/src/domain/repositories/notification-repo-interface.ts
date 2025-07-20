import type { Notification } from "@domain/entities/notification";

export interface INotificationRepository{
    getNotificationById(notificationId: string): Promise<Notification | null>;
    getNotificationsByInboxId(inboxId: string, limit?: number, skip?: number): Promise<Notification[]>;
    createNotification(notification: Notification): Promise<Notification>;
    updateNotification(notificationId: string, update: Partial<Notification>): Promise<Notification | null>;
}
