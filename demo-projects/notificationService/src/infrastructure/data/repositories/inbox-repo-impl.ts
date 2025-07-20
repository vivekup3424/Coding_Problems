import { Inbox } from "@domain/entities/inbox";
import type { IInboxRepository, InboxOperationResult } from "@domain/repositories/inbox-repo-interface";
import type { MongoClientAdapter } from "@infrastructure/adapters/mongodb";
import type { Collection, Db } from "mongodb";

export class InboxRepository implements IInboxRepository {
    private mongoClient: MongoClientAdapter;
    private inboxDbName = "notificationService"; // database name
    private inboxCollectionName = "inboxes"; // collection name
    private inboxDb: Db;
    private inboxCollection: Collection<Inbox>;

    constructor(mongoAdapter: MongoClientAdapter) {
        this.mongoClient = mongoAdapter;
        this.inboxDb = this.mongoClient.client.db(this.inboxDbName);
        this.inboxCollection = this.inboxDb.collection<Inbox>(this.inboxCollectionName);
    }

    async getInboxById(inboxId: string): Promise<Inbox | null> {
        return await this.inboxCollection.findOne({ id: inboxId });
    }

    async getInboxesByUserId(userId: string): Promise<Inbox[]> {
        return await this.inboxCollection.find({ userId }).toArray();
    }

    async createInbox(inbox: Inbox): Promise<Inbox> {
        await this.inboxCollection.insertOne(inbox);
        return inbox;
    }

    async updateInbox(inboxId: string, update: Partial<Inbox>): Promise<Inbox | null> {
        const result = await this.inboxCollection.findOneAndUpdate(
            { id: inboxId },
            { $set: update },
            { returnDocument: "after" }
        );
        return result;
    }

    async deleteInbox(inboxId: string): Promise<boolean> {
        const result = await this.inboxCollection.deleteOne({ id: inboxId });
        return result.deletedCount === 1;
    }

    async clearInbox(inboxId: string): Promise<InboxOperationResult> {
        // This method could be used to trigger notification cleanup in NotificationRepository
        // Here, just a stub for interface compatibility
        const inbox = await this.getInboxById(inboxId);
        if (!inbox) {
            return { success: false, error: "Inbox not found" };
        }
        // Actual notification cleanup should be handled in NotificationRepository
        return { success: true };
    }
}
