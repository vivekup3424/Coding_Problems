enum NotificationStatus {
    READ = "read",
    UNREAD = "unread",
}
interface IInboxNotification {
    _id: string;
    notificationId: string;
    inboxId: string;
    userId: string;
    status: NotificationStatus;
    createdAt: Date;
    readAt?: Date;
    expiresAt: Date;
}

export type {IInboxNotification};