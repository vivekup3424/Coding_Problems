import { createContainer, asClass,InjectionMode, type AwilixContainer } from "awilix";
import { Logger } from "@infrastructure/logging";
import { SendNotificationUsecase } from "@domain/use-cases/send-notification.usecase";
import type { IDependencies } from "./interface";
import { MongoClientAdapter } from "@infrastructure/adapters/mongodb";
import { NotificationRepository } from "@infrastructure/data/repositories/notification-repo-impl";
import { InboxRepository } from "@infrastructure/data/repositories/inbox-repo-impl";
import { MoleculerBrokerAdapter } from "@infrastructure/adapters/moleculer/service-broker-adapter";
const diContainer: AwilixContainer<IDependencies> = createContainer({
    injectionMode: InjectionMode.PROXY,
    strict: true
});
diContainer.register({
    logger: asClass(Logger).singleton(),
    sendNotificationUsecase: asClass(SendNotificationUsecase).singleton(),
    mongoClientAdapter: asClass(MongoClientAdapter).singleton(),
    moleculerBrokerAdapter: asClass(MoleculerBrokerAdapter).singleton(),
    notificationRepository: asClass(NotificationRepository).singleton(),
    inboxRepository: asClass(InboxRepository).singleton(),
});
export { diContainer}