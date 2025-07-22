enum NotificationStatus {
    PENDING = 'PENDING',
    READ = 'READ',
    ARCHIVED = 'ARCHIVED',
    FAILED = 'FAILED',
    SENT = 'SENT',
    UNREAD = 'UNREAD',
}

enum NotificationType {
    EMAIL = 'EMAIL',
    SMS = 'SMS',
    PUSH = 'PUSH',
    IN_APP = 'IN_APP',
    WHATSAPP = 'WHATSAPP',
}
interface NotificationContentBase {
    locale?: string;
    body: string;
    [key: string]: any;
}

interface NotificationBase {
    _id: string;
    notificationId: string;
    userId: string;
    createdAt: Date;
    expiresAt?: Date;
    deliveredAt?: Date;
    event: string;
    deliveryStatus: NotificationStatus;
}
interface EmailContent extends NotificationContentBase {
    subject: string;
    sender_name: string;
}

interface WhatsAppContent extends NotificationContentBase {
    template_name: string;
    header?: object;
    button?: object;
    locale: string;
    replacements: Record<string, string>;
}

interface SMSContent extends NotificationContentBase {
    template_id?: string;
    message_info?: Record<string, any>;
}

interface PushContent extends NotificationContentBase {
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
    large_icon?: string;
}
type Notification =
    | (NotificationBase & { type: NotificationType.EMAIL; content: EmailContent })
    | (NotificationBase & { type: NotificationType.SMS; content: SMSContent })
    | (NotificationBase & { type: NotificationType.PUSH; content: PushContent })
    | (NotificationBase & { type: NotificationType.WHATSAPP; content: WhatsAppContent });


export type {Notification}