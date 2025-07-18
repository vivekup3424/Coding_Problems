import type { Inbox } from "@domain/entities/inbox";

export interface InboxOperationResult {
    success: boolean;
    error ?: string;
    data ?: string;
}
export interface InboxRepositoryInterface {
    getInboxById(inboxId: string): Promise<Inbox | null>;
    createInbox(inbox: Inbox): Promise<Inbox>;
    AddNotificationToInbox(inboxId: string, notificationId: string): Promise<InboxOperationResult>;
    MarkNotificationAsRead(inboxId: string, notificationId: string): Promise<InboxOperationResult>;
    clearInbox(inboxId: string): Promise<InboxOperationResult>;
}