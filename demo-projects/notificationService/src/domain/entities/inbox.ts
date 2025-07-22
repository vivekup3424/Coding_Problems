import { NotificationStatus } from "./notification";

// Entity: Inbox
export class Inbox{
    inboxId: string;
    notificationId: string;
    userId: string;
    status: NotificationStatus;
    createdAt: Date;
    readAt?: Date;
    expiresAt: Date;
    constructor(inboxId: string, userId: string, notificationId: string, status: NotificationStatus, createdAt: Date, readAt: Date | undefined, expiresAt: Date) {
        this.inboxId = inboxId;
        this.userId = userId;
        this.notificationId = notificationId;
        this.status = status;
        this.createdAt = createdAt;
        this.readAt = readAt;
        this.expiresAt = expiresAt;
    }

    getId(): string {
        return this.inboxId;
    }

    getNotificationId(): string {
        return this.notificationId;
    }

    getUserId(): string {
        return this.userId;
    }
}
