import type { Inbox } from "@domain/entities/inbox";

export interface InboxOperationResult {
    success: boolean;
    error?: string;
    data?: string;
}

export interface IInboxRepository {
    getInboxById(inboxId: string): Promise<Inbox | null>;
    getInboxesByUserId(userId: string): Promise<Inbox[]>;
    createInbox(inbox: Inbox): Promise<Inbox>;
    updateInbox(inboxId: string, update: Partial<Inbox>): Promise<Inbox | null>;
    deleteInbox(inboxId: string): Promise<boolean>;
    clearInbox(inboxId: string): Promise<InboxOperationResult>;
}