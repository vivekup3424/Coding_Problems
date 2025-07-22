export interface Inbox {
    _id: string;
    notificationCleanupInterval: number; // in days
    notificationIds : string[];
}
