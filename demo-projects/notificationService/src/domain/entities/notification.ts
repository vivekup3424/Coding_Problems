import { EVENT } from './events';
enum NotificationStatus {
    PENDING = 'PENDING',
    READ = 'READ',
    ARCHIVED = 'ARCHIVED',
    FAILED = 'FAILED',
    SENT = 'SENT',
    UNREAD = 'UNREAD'
}
enum NotificationType {
    EMAIL = 'EMAIL',
    SMS = 'SMS',
    PUSH = 'PUSH',
    IN_APP = 'IN_APP',
    WHATSAPP = 'WHATSAPP',
}

// Base content interface for all notifications
interface NotificationContent {
    locale?: string;
    body: string;
    [key: string]: any; // Allow extension for channel-specific fields
}

interface Notification {
    id: string;
    status: NotificationStatus;
    createdAt: Date;
    expiresAt?: Date;
    deliveredAt?: Date;
    readAt?: Date;
    userIdentifier: string; // Unique identifier for the user (for clevertap purpose)
    event?: EVENT;
    content: NotificationContent;
}


// Channel-specific content interfaces
interface EmailContent extends NotificationContent {
    subject: string;
    sender_name: string;
}

interface WhatsAppContent extends NotificationContent {
    template_name: string;
    header?: object;
    button?: object;
    locale: string;
    replacements: Record<string, string>;
}

interface SMSContent extends NotificationContent {
    template_id?: string;
    message_info?: Record<string,any>;
}

interface PushContent extends NotificationContent {
    title: string;
    subtitle?: string;
    button: object;
    locale: string;
    platform_specific?: object;
    background_image?: string;
    notification_tray_priority?: "max" | "high" | "default";
    delivery_priority?: "high" | "normal";
    android_collapse?: string | number;
    ios_collapse?: string | number;
    large_icon?: string; // URL for large icon
}
// Channel-specific notification interfaces
interface EmailNotification extends Notification {
    type: NotificationType.EMAIL;
    content: EmailContent;
}

interface WhatsAppNotification extends Notification {
    type: NotificationType.WHATSAPP;
    content: WhatsAppContent;
}

interface SMSNotification extends Notification {
    type: NotificationType.SMS;
    content: SMSContent;
}

interface PushNotification extends Notification {
    type: NotificationType.PUSH;
    content: PushContent;
}
export type {
    Notification,
    EmailNotification,
    WhatsAppNotification,
    SMSNotification,
    PushNotification,
    NotificationType,
    NotificationStatus,
    EVENT,
    NotificationContent,
    EmailContent,
    WhatsAppContent,
    SMSContent,
    PushContent
}