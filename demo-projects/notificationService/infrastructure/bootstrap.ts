import { ServiceBroker } from "moleculer";
import { Container } from "./di/Container";
import { InMemoryNotificationRepository } from "./repositories/InMemoryNotificationRepository";
import { InMemoryTemplateRepository } from "./repositories/InMemoryTemplateRepository";
import { InMemoryTopicRepository } from "./repositories/InMemoryTopicRepository";
import { InMemorySubscriberRepository } from "./repositories/InMemorySubscriberRepository";
import { MongoNotificationRepository } from "./repositories/MongoNotificationRepository";
import { MongoTemplateRepository } from "./repositories/MongoTemplateRepository";
import { MongoTopicRepository } from "./repositories/MongoTopicRepository";
import { MongoSubscriberRepository } from "./repositories/MongoSubscriberRepository";
import { MongoConnection } from "./database/MongoConnection";
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
import type { INotificationProvider } from "../domain/ports/INotificationProvider";
import { loadConfig, type AppConfig } from "../config/config";
import 'dotenv/config';

export const SERVICE_IDENTIFIERS = {
  AppConfig: "AppConfig",
  ServiceBroker: "ServiceBroker",
  Container: "Container",
  DomainEventPublisher: "DomainEventPublisher",
  NotificationRepository: "NotificationRepository",
  TemplateRepository: "TemplateRepository",
  TopicRepository: "TopicRepository",
  SubscriberRepository: "SubscriberRepository",
  NotificationDomainService: "NotificationDomainService",
  SendNotificationUseCase: "SendNotificationUseCase",
  MarkNotificationAsReadUseCase: "MarkNotificationAsReadUseCase",
  NotificationApplicationService: "NotificationApplicationService",
  TopicApplicationService: "TopicApplicationService",
  SubscriberApplicationService: "SubscriberApplicationService",
  ProviderRegistry: "ProviderRegistry",
  EmailProviderAdapter: "EmailProviderAdapter",
  SMSProviderAdapter: "SMSProviderAdapter",
  PushProviderAdapter: "PushProviderAdapter",
  NotificationController: "NotificationController",
  TopicController: "TopicController",
  SubscriberController: "SubscriberController",
  Database: "Database"
};

/**
 * Configuration props are now moved to config.ts
 */
export interface BootstrapConfig {
  smsConfig: SMSConfig;
  pushConfig: PushConfig;
  emailConfig: EmailConfig;
  mediumRetryCount: number;
}

/**
 * Bootstrap the application with all dependencies
 */
export async function bootstrap(config: BootstrapConfig): Promise<{
  broker: ServiceBroker;
  container: Container;
}> {
  // Load application configuration
  const appConfig = loadConfig();
  
  // Create service broker
  const broker = new ServiceBroker({ 
    logLevel: process.env.NODE_ENV === "production" ? "info" : "debug"
  });

  // Create container
  const container = new Container();
  
  // Register config
  container.register(SERVICE_IDENTIFIERS.AppConfig, appConfig);
  
  // Register domain event publisher
  const eventPublisher = new MoleculerEventAdapter(broker);
  container.register(SERVICE_IDENTIFIERS.DomainEventPublisher, eventPublisher);
  
  // Initialize MongoDB connection if not using in-memory database
  if (!appConfig.database.useInMemory) {
    try {
      console.log(`Attempting to connect to MongoDB at ${appConfig.database.uri}...`);
      const mongoConnection = MongoConnection.getInstance();
      await mongoConnection.connect(appConfig.database.uri);
      console.log('Connected to MongoDB database successfully');
    } catch (error) {
      console.error('Failed to connect to MongoDB. Falling back to in-memory database', error);
      // Force using in-memory database if MongoDB connection fails
      appConfig.database.useInMemory = true;
    }
  } else {
    console.log('Using in-memory database as configured');
  }
  
  // Register repositories based on configuration
  if (appConfig.database.useInMemory) {
    console.log('Using in-memory repositories');
    
    const notificationRepository = new InMemoryNotificationRepository();
    container.register(SERVICE_IDENTIFIERS.NotificationRepository, notificationRepository);

    const templateRepository = new InMemoryTemplateRepository();
    container.register(SERVICE_IDENTIFIERS.TemplateRepository, templateRepository);

    const topicRepository = new InMemoryTopicRepository();
    container.register(SERVICE_IDENTIFIERS.TopicRepository, topicRepository);

    const subscriberRepository = new InMemorySubscriberRepository();
    container.register(SERVICE_IDENTIFIERS.SubscriberRepository, subscriberRepository);
  } else {
    console.log('Using MongoDB repositories');
    
    const notificationRepository = new MongoNotificationRepository();
    container.register(SERVICE_IDENTIFIERS.NotificationRepository, notificationRepository);

    const templateRepository = new MongoTemplateRepository();
    container.register(SERVICE_IDENTIFIERS.TemplateRepository, templateRepository);

    const topicRepository = new MongoTopicRepository();
    container.register(SERVICE_IDENTIFIERS.TopicRepository, topicRepository);

    const subscriberRepository = new MongoSubscriberRepository();
    container.register(SERVICE_IDENTIFIERS.SubscriberRepository, subscriberRepository);
  }
  
  // Register domain services
  const notificationDomainService = new NotificationDomainService();
  container.register(SERVICE_IDENTIFIERS.NotificationDomainService, notificationDomainService);
  
  // Register provider registry and providers
  const providerRegistry = new ProviderRegistry();
  const emailProvider = new EmailProviderAdapter(config.emailConfig);
  providerRegistry.registerProvider(emailProvider);
  container.register(SERVICE_IDENTIFIERS.EmailProviderAdapter, emailProvider);

  const smsProvider = new SMSProviderAdapter(config.smsConfig);
  providerRegistry.registerProvider(smsProvider);
  container.register(SERVICE_IDENTIFIERS.SMSProviderAdapter, smsProvider);

  const pushProvider = new PushProviderAdapter(config.pushConfig);
  providerRegistry.registerProvider(pushProvider);
  container.register(SERVICE_IDENTIFIERS.PushProviderAdapter, pushProvider);
  container.register(SERVICE_IDENTIFIERS.ProviderRegistry, providerRegistry);
  
  // Prepare providers for SendNotificationUseCase config
  const providersRecord: Record<string, INotificationProvider> = {};
  providerRegistry.getAllProviders().forEach(p => {
    providersRecord[p.getChannel()] = p;
  });

  // Register use cases
  const sendNotificationUseCase = new SendNotificationUseCase(
    { providers: providersRecord, mediumRetryCount: config.mediumRetryCount }, // Corrected providers format
    container.get(SERVICE_IDENTIFIERS.NotificationRepository),
    container.get(SERVICE_IDENTIFIERS.TemplateRepository),
    notificationDomainService,
    eventPublisher
  );
  container.register(SERVICE_IDENTIFIERS.SendNotificationUseCase, sendNotificationUseCase);

  const markNotificationAsReadUseCase = new MarkNotificationAsReadUseCase(
    container.get(SERVICE_IDENTIFIERS.NotificationRepository),
    eventPublisher
  );
  container.register(SERVICE_IDENTIFIERS.MarkNotificationAsReadUseCase, markNotificationAsReadUseCase);
  
  // Register application services
  const notificationApplicationService = new NotificationApplicationService(
    container.get(SERVICE_IDENTIFIERS.SendNotificationUseCase),
    container.get(SERVICE_IDENTIFIERS.MarkNotificationAsReadUseCase),
    container.get(SERVICE_IDENTIFIERS.NotificationRepository),
    container.get(SERVICE_IDENTIFIERS.DomainEventPublisher) // Corrected: pass event publisher
  );
  container.register(SERVICE_IDENTIFIERS.NotificationApplicationService, notificationApplicationService);
  
  const topicApplicationService = new TopicApplicationService(
    container.get(SERVICE_IDENTIFIERS.TopicRepository),
    container.get(SERVICE_IDENTIFIERS.SubscriberRepository)
  );
  container.register(SERVICE_IDENTIFIERS.TopicApplicationService, topicApplicationService);
  
  const subscriberApplicationService = new SubscriberApplicationService(
    container.get(SERVICE_IDENTIFIERS.SubscriberRepository),
    container.get(SERVICE_IDENTIFIERS.DomainEventPublisher) // Corrected: added event publisher
  );
  container.register(SERVICE_IDENTIFIERS.SubscriberApplicationService, subscriberApplicationService);
  
  // Register controllers (if they were to be resolved from container, which they are not in current setup)
  // but for completeness, if they were:
  // const notificationController = new NotificationController(notificationApplicationService, topicApplicationService);
  // container.register(SERVICE_IDENTIFIERS.NotificationController, notificationController);
  // const topicController = new TopicController(topicApplicationService);
  // container.register(SERVICE_IDENTIFIERS.TopicController, topicController);
  // const subscriberController = new SubscriberController(subscriberApplicationService);
  // container.register(SERVICE_IDENTIFIERS.SubscriberController, subscriberController);

  // Start broker
  await broker.start();

  // Create API service for controllers
  broker.createService({
    name: "notification-api",
    mixins: [
      NotificationController,
      TopicController,
      SubscriberController,
    ],
    settings: {
      container, // Provide container to services if needed for DI within Moleculer services
      // Pass specific services if preferred over passing the whole container
      notificationApplicationService,
      topicApplicationService,
      subscriberApplicationService
    },
    // If your controllers are classes, you might need to instantiate them or adapt them to Moleculer's service schema.
    // The current structure of controllers seems to be objects with methods, which should be compatible.
  });

  // Create worker service (example, if you have background tasks)
  broker.createService({
    name: "notification-workers",
    // actions, events, methods for worker tasks
    // e.g., listening to domain events and processing them
    events: {
      "domain.notification.created": {
        group: "notification-processing",
        async handler(ctx: any) {
          console.log(`[Worker] Received notification.created event for notification ID: ${ctx.params.notificationId}`);
          // Example: Trigger further processing, like attempting to send via SendNotificationUseCase
          // This is a simplified example; in a real app, you'd avoid re-triggering the same use case directly from an event it emits
          // unless there's a clear state distinction (e.g., created -> pending_dispatch -> dispatched)
        }
      },
      "domain.notification.sent": {
        group: "notification-logging",
        async handler(ctx: any) {
          console.log(`[Worker] Notification ID ${ctx.params.notificationId} sent successfully via ${ctx.params.provider}.`);
        }
      },
      "domain.notification.failed": {
        group: "notification-failure-handling",
        async handler(ctx: any) {
          console.log(`[Worker] Notification ID ${ctx.params.notificationId} failed to send. Reason: ${ctx.params.error}`);
          // Example: Log failure, schedule retry, notify admin, etc.
        }
      }
    }
  });

  return { broker, container };
}
