import type { Notification } from "@domain/entities/notification";

export interface RepositoryResponse<T> {
    success: boolean;
    error?: string;
    data?: T;
}

export interface INotificationRepository {
    getNotificationById(notificationId: string): Promise<RepositoryResponse<Notification>>;
    createNotification(notification: Notification): Promise<RepositoryResponse<Notification>>;
    updateNotification(notificationId: string, update: Partial<Notification>): Promise<RepositoryResponse<Notification>>;
    deleteNotification(notificationId: string): Promise<RepositoryResponse<null>>;
    getNotificationsByUserId(userId: string, offset?: number, limit?: number): Promise<RepositoryResponse<Notification[]>>;
}