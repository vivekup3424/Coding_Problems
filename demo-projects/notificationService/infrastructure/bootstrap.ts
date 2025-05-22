import { ServiceBroker } from "moleculer";
import { Container } from "./di/Container";
import { InMemoryNotificationRepository } from "./repositories/InMemoryNotificationRepository";
import { InMemoryTemplateRepository } from "./repositories/InMemoryTemplateRepository";
import { InMemoryTopicRepository } from "./repositories/InMemoryTopicRepository";
import { InMemorySubscriberRepository } from "./repositories/InMemorySubscriberRepository";
import { NotificationDomainService } from "../domain/services/NotificationDomainService";
import { SendNotificationUseCase } from "../application/useCases/SendNotificationUseCase";
import { MarkNotificationAsReadUseCase } from "../application/useCases/MarkNotificationAsReadUseCase";
import { NotificationApplicationService } from "../application/services/NotificationApplicationService";
import { TopicApplicationService } from "../application/services/TopicApplicationService";
import { SubscriberApplicationService } from "../application/services/SubscriberApplicationService";
import { MoleculerEventAdapter } from "./adapters/MoleculerEventAdapter";
import { NotificationProviderAdapter } from "./adapters/NotificationProviderAdapter";
import { NotificationController } from "../interfaces/api/NotificationController";
import { TopicController } from "../interfaces/api/TopicController";
import { SubscriberController } from "../interfaces/api/SubscriberController";
import { 
  EmailProviderAdapter, 
  SMSProviderAdapter, 
  PushProviderAdapter,
  ProviderRegistry 
} from "./adapters/providers";
import type { EmailConfig } from "./adapters/providers/EmailProviderAdapter";
import type { SMSConfig } from "./adapters/providers/SMSProviderAdapter";
import type { PushConfig } from "./adapters/providers/PushProviderAdapter";
import 'dotenv/config';

export interface AppConfig {
  smsConfig: SMSConfig;
  pushConfig: PushConfig;
  emailConfig: EmailConfig;
  mediumRetryCount: number;
}

/**
 * Bootstrap the application with all dependencies
 */
export async function bootstrap(config: AppConfig): Promise<{
  broker: ServiceBroker;
  container: Container;
}> {
  // Create service broker
  const broker = new ServiceBroker({ 
    logLevel: process.env.NODE_ENV === "production" ? "info" : "debug"
  });

  // Create container
  const container = new Container();
  
  // Register domain event publisher
  const eventPublisher = new MoleculerEventAdapter(broker);
  container.register("domainEventPublisher", eventPublisher);
  
  // Register repositories
  const notificationRepository = new InMemoryNotificationRepository();
  const templateRepository = new InMemoryTemplateRepository();
  const topicRepository = new InMemoryTopicRepository();
  const subscriberRepository = new InMemorySubscriberRepository();
  container.register("notificationRepository", notificationRepository);
  container.register("templateRepository", templateRepository);
  container.register("topicRepository", topicRepository);
  container.register("subscriberRepository", subscriberRepository);
  
  // Register clean architecture providers
  const smsProviderAdapter = new SMSProviderAdapter(config.smsConfig);
  const pushProviderAdapter = new PushProviderAdapter(config.pushConfig);
  const emailProviderAdapter = new EmailProviderAdapter(config.emailConfig);
  
  // Create and configure provider registry
  const providerRegistry = new ProviderRegistry();
  providerRegistry.registerProvider(smsProviderAdapter);
  providerRegistry.registerProvider(pushProviderAdapter);
  providerRegistry.registerProvider(emailProviderAdapter);
  container.register("providerRegistry", providerRegistry);
  
  // Create legacy notification provider adapters for backward compatibility
  const notificationProviderSMS = new NotificationProviderAdapter(smsProviderAdapter);
  const notificationProviderPush = new NotificationProviderAdapter(pushProviderAdapter);
  const notificationProviderEmail = new NotificationProviderAdapter(emailProviderAdapter);
  
  // Register provider adapters
  container.register("provider.sms", notificationProviderSMS);
  container.register("provider.push", notificationProviderPush);
  container.register("provider.email", notificationProviderEmail);
  
  // Register domain services
  const notificationDomainService = new NotificationDomainService();
  container.register("notificationDomainService", notificationDomainService);
  
  // Configure use cases
  const sendNotificationUseCase = new SendNotificationUseCase(
    {
      providers: {
        sms: notificationProviderSMS,
        push: notificationProviderPush,
        email: notificationProviderEmail
      },
      mediumRetryCount: config.mediumRetryCount
    },
    notificationRepository,
    templateRepository,
    notificationDomainService,
    eventPublisher
  );
  container.register("sendNotificationUseCase", sendNotificationUseCase);
  
  const markAsReadUseCase = new MarkNotificationAsReadUseCase(
    notificationRepository,
    eventPublisher
  );
  container.register("markAsReadUseCase", markAsReadUseCase);
  
  // Register application services
  const notificationApplicationService = new NotificationApplicationService(
    sendNotificationUseCase,
    markAsReadUseCase,
    notificationRepository,
    templateRepository
  );
  container.register("notificationApplicationService", notificationApplicationService);
  
  // Register Topic and Subscriber application services
  const topicApplicationService = new TopicApplicationService(
    topicRepository,
    subscriberRepository
  );
  container.register("topicApplicationService", topicApplicationService);
  
  const subscriberApplicationService = new SubscriberApplicationService(
    subscriberRepository,
    topicRepository
  );
  container.register("subscriberApplicationService", subscriberApplicationService);
  
  // Register controllers
  const notificationController = new NotificationController(
    broker, 
    sendNotificationUseCase,
    markAsReadUseCase,
    notificationRepository,
    templateRepository
  );
  container.register("notificationController", notificationController);
  
  const topicController = new TopicController(topicApplicationService);
  container.register("topicController", topicController);
  
  const subscriberController = new SubscriberController(subscriberApplicationService);
  container.register("subscriberController", subscriberController);
  
  // Define broker handlers for job processing
  broker.createService({
    name: "notification-workers",
    actions: {
      sendHigh: {
        handler: async (ctx: any) => {
          const { notification } = ctx.params;
          return sendNotificationUseCase.execute({
            templateId: notification.templateId,
            subscriberId: notification.subscriberId,
            topicId: notification.topicId,
            provider: notification.provider,
            payload: notification.payload,
            criticality: notification.criticality
          });
        },
      }
    },
    events: {
      "notification.sendLow": async (ctx: any) => {
        const { notification } = ctx.params;
        try {
          await sendNotificationUseCase.execute({
            templateId: notification.templateId,
            subscriberId: notification.subscriberId,
            topicId: notification.topicId,
            provider: notification.provider,
            payload: notification.payload,
            criticality: notification.criticality
          });
        } catch (err) {
          broker.logger.error("Error sending low priority notification:", err);
        }
      }
    }
  });
  
  // Start the broker
  await broker.start();
  
  return { broker, container };
}
