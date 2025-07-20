// Entity: Inbox
export class Inbox {
    id: string;
    notificationCleanupInterval: number; // in days
    userId: string;
    constructor(id: string, userId: string, notificationCleanupInterval: number) {
        this.id = id;
        this.userId = userId;
        this.notificationCleanupInterval = notificationCleanupInterval;
    }

    getId(): string {
        return this.id;
    }

    getNotificationCleanupInterval(): number {
        return this.notificationCleanupInterval;
    }
    getUserId(): string{
        return this.userId;
    }
}
