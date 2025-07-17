interface Inbox {
    id: string;
    notiticationCleanupInterval: number; // in days
    addNotification(message: string): void;
    getNotifications(offset: number, batchSize: number): string[];
    clearNotifications(): void;
    markNotificationAsRead(messageId: string): void;
    archiveNotification(messageId: string): void;
}
//archive notification gets deleted from inbox after a certain time
enum NotificationStatus {
    PENDING = 'PENDING',
    READ = 'READ',
    ARCHIVED = 'ARCHIVED',
    FAILED = 'FAILED',
    SENT = 'SENT',
    UNREAD = 'UNREAD'
}
enum EVENT {
    CAMERA_VIEWED = 'CAMERA_VIEWED',
    MOTION_DETECTID = 'MOTION_DETECTED',
}
enum NotificationType {
    EMAIL = 'EMAIL',
    SMS = 'SMS',
    PUSH = 'PUSH',
    IN_APP = 'IN_APP',
    WHATSAPP = 'WHATSAPP',
}
interface Notification {
    id: string;
    status: NotificationStatus;
    createdAt: Date;
    expiresAt?: Date;
    deliveredAt?: Date;
    readAt?: Date;
}
interface User {
    id: string;
    identifier: string; // Unique identifier for the user(for clevertap purpose)
    name: string;
    email: string;
    phoneNumber: string;
    deviceId: string[]; // For push notifications
    siteId: string; // unique identifier for the home
    gatewayId: string; //unque identifier for the hub inside home
}

interface EmailNotification extends Notification {
    type: NotificationType.EMAIL;
    content: {
        subject: string;
        body: string;
        sender_name: string;
        [key: string]: any; // Additional properties can be added
    }
}
interface WhatsAppNotification extends Notification {
    type: NotificationType.WHATSAPP;
    content:{
        template_name: string;
        header: Object;
        body: Object;
        button: Object;
        locale: string
    }
}

interface SMSNotification extends Notification {
    type: NotificationType.SMS;
    content: {
        body: string;
        recipientPhoneNumber: string;
    }
}
interface PushNotification extends Notification {
    type: NotificationType.PUSH;
    content: {
        title: string;
        body: string;
        button: Object;
        locale: string
    },
    platform_specific: string;
    background_image?: string;
    notification_tray_priority: "max" | "high" | "default";
}

interface CleverTapCampaign {
    name: string;
    provider_nick_name?: string;
    "content.sms.template_id": string;
    conversion_goal?: {
        event_name: string;
        filter_type: object;
    },
    where: {
        event_name?: string;
        from?: number; //date
        to?: number;
        profile_fields: number;
    }
    send_to_all_devices: boolean;
    content: {
        title: string;
        body: string;
        subject: string;
        sender_name: string;
        template_name: string;
    }

}