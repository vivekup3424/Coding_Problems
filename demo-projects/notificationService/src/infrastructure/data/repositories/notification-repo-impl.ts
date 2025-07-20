import { Inbox } from "@domain/entities/inbox";
import type { IInboxRepository, InboxOperationResult } from "@domain/repositories/inbox-repo-interface";
import type { MongoClientAdapter } from "@infrastructure/adapters/mongodb";
import type { Collection, Db } from "mongodb";
import { Logger } from "@infrastructure/logging";
import type { INotificationRepository } from "@domain/repositories/notification-repo-interface";
import { Notification } from "@domain/entities/notification";

export class NotificationRepository implements INotificationRepository {
    private dbClient: MongoClientAdapter;
    private dbName = "notifications";
    private db: Db;
    private collection: Collection<Notification>;
    private logger: Logger;

    constructor(mongoClient: MongoClientAdapter, logger: Logger) {
        this.dbClient = mongoClient;
        this.logger = logger;
        this.db = this.dbClient.client.db(this.dbName);
        this.collection = this.db.collection<Notification>("notifications");
    }

    async getNotificationById(notificationId: string): Promise<Notification | null> {
        try {
            const notification = await this.collection.findOne({ _id: notificationId });
            return notification;
        } catch (error) {
            this.logger.error(`Failed to get notification by id: ${notificationId}: ${error instanceof Error ? error.message : String(error)}`);
            throw error;
        }
    }

    async getNotificationsByInboxId(inboxId: string, limit = 10, skip = 0): Promise<Notification[]> {
        try {
            const notifications = await this.collection
                .find({ inboxId })
                .skip(skip)
                .limit(limit)
                .toArray();
            return notifications;
        } catch (error) {
            this.logger.error(`Failed to get notifications for inbox: ${inboxId}: ${error instanceof Error ? error.message : String(error)}`);
            throw error;
        }
    }

    async createNotification(notification: Notification): Promise<Notification> {
        try {
            await this.collection.insertOne(notification);
            return notification;
        } catch (error) {
            this.logger.error(`Failed to create notification: ${error instanceof Error ? error.message : String(error)}`);
            throw error;
        }
    }

    async updateNotification(notificationId: string, update: Partial<Notification>): Promise<Notification | null> {
        try {
            const result = await this.collection.findOneAndUpdate(
                { _id: notificationId },
                { $set: update },
                { returnDocument: "after" }
            );
            return result;
        } catch (error) {
            this.logger.error(`Failed to update notification: ${notificationId}: ${error instanceof Error ? error.message : String(error)}`);
            throw error;
        }
    }
}