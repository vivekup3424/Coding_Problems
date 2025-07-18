interface Inbox {
    id: string;
    notiticationCleanupInterval: number; // in days
    addNotification(message: string): void;
    getNotifications(offset: number, batchSize: number): string[];
    clearNotifications(): void;
    markNotificationAsRead(messageId: string): void;
    archiveNotification(messageId: string): void;
}

export type {
    Inbox
}