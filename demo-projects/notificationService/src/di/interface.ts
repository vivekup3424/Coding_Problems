import type { Logger } from "@infrastructure/logging";
import type { SendNotificationUsecase } from "@domain/use-cases/send-notification.usecase";
import type { IInboxRepository } from "@domain/repositories/inbox-repo-interface";
import type { MongoClientAdapter } from "@infrastructure/adapters/mongodb";
import type { MoleculerBrokerAdapter } from "@infrastructure/adapters/moleculer/service-broker-adapter";
import type { NotificationRepository } from "@infrastructure/data/repositories/notification-repo-impl";
import type { InboxRepository } from "@infrastructure/data/repositories/inbox-repo-impl";
export interface IDependencies{
    logger: Logger;
    sendNotificationUsecase: SendNotificationUsecase;
    notificationRepository: NotificationRepository;
    inboxRepository: InboxRepository;
    mongoClientAdapter: MongoClientAdapter;
    moleculerBrokerAdapter: MoleculerBrokerAdapter;
}