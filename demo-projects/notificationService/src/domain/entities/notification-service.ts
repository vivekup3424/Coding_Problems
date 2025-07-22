import { NotificationStatus, EVENT, NotificationType, type EmailContent, type WhatsAppContent, type SMSContent, type PushContent } from "./notification";

interface Inbox {
    inboxId: string;
    notificationId: string;
    userId: string;
    status: NotificationStatus;
    createdAt: Date;
    readAt?: Date;
    expiresAt: Date;
}
interface Notification {
    _id: string;
    notificationId: string;
    userId: string; // Unique identifier for the user (for clevertap purpose)
    createdAt: Date;
    expiresAt?: Date;
    deliveredAt?: Date;
    event?: EVENT;
    type: NotificationType;
    content: EmailContent | WhatsAppContent | SMSContent | PushContent; // Channel-specific content
}
export interface Response {
    success: boolean;
    data?: string;
    error?: string;
}
interface sendNotificationResponse {
    success: boolean;
    data?: {
        notificationId: string;
        message: string;
    };
    error?: string;
}
interface GetNotificationResponse {
    success: boolean;
    data?: {
        "notifications": Notification[];
        "totalCount": number;
        "offset": number;
        "limit": number;
        "hasMore": boolean;
    };
    error?: string;
}
export interface INotificationService {

    sendNotification(notification: Notification, saveToInboxId: string): Promise<sendNotificationResponse>;

    markNotificationAsReadInInbox(notificationId: string, inboxId: string): Promise<Response>;

    getNotificationsFromInbox(inboxId: string, offset: number, limit: number): Promise<GetNotificationResponse>;

}