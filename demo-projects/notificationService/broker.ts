import 'dotenv/config';
import { ServiceBroker, Context } from "moleculer";
import { bootstrap } from "./infrastructure/bootstrap";
import type { AppConfig } from "./infrastructure/bootstrap";
import type { SendNotificationInput } from "./application/useCases/SendNotificationUseCase";

const config: AppConfig = {
  smsConfig: { 
    accessToken: process.env.SMS_TOKEN || "" 
  },
  pushConfig: { 
    firebaseConfig: {
      projectId: process.env.FIREBASE_PROJECT_ID || '',
      clientEmail: process.env.FIREBASE_CLIENT_EMAIL || '',
      privateKey: process.env.FIREBASE_PRIVATE_KEY?.replace(/\\n/g, "\n") || '',
    }
  },
  emailConfig: { 
    transportOptions: {
      host: process.env.SMTP_HOST || '',
      port: Number(process.env.SMTP_PORT) || 587,
      secure: false,
      auth: { 
        user: process.env.SMTP_USER || '', 
        pass: process.env.SMTP_PASS || '' 
      }
    }
  },
  mediumRetryCount: Number(process.env.MEDIUM_RETRY_COUNT) || 3,
};

// Initialize broker
let broker: ServiceBroker;
let container: any;

// Bootstrap application with dependencies
(async () => {
  try {
    console.log('Initializing notification service broker...');
    
    // Bootstrap the application with DI container
    const app = await bootstrap(config);
    broker = app.broker;
    container = app.container;
    
    // Register service endpoints for topics
    broker.createService({
      name: "topic-service",
      actions: {
        create: {
          params: {
            name: "string",
            description: { type: "string", optional: true }
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.createTopic(ctx);
          }
        },
        get: {
          params: {
            id: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.getTopic(ctx);
          }
        },
        list: {
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.listTopics();
          }
        },
        update: {
          params: {
            id: "string",
            name: { type: "string", optional: true },
            description: { type: "string", optional: true }
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.updateTopic(ctx);
          }
        },
        delete: {
          params: {
            id: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.deleteTopic(ctx);
          }
        },
        subscribe: {
          params: {
            topicId: "string",
            subscriberId: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.subscribeTopic(ctx);
          }
        },
        unsubscribe: {
          params: {
            topicId: "string",
            subscriberId: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const topicController = container.get("topicController");
            return topicController.unsubscribeTopic(ctx);
          }
        }
      }
    });
    
    // Register service endpoints for subscribers
    broker.createService({
      name: "subscriber-service",
      actions: {
        create: {
          params: {
            firstName: "string",
            lastName: "string",
            email: { type: "string", optional: true },
            phoneNumber: { type: "string", optional: true },
            pushTokens: { type: "array", items: "string", optional: true }
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.createSubscriber(ctx);
          }
        },
        get: {
          params: {
            id: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.getSubscriber(ctx);
          }
        },
        list: {
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.listSubscribers();
          }
        },
        update: {
          params: {
            id: "string",
            firstName: { type: "string", optional: true },
            lastName: { type: "string", optional: true },
            email: { type: "string", optional: true },
            phoneNumber: { type: "string", optional: true }
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.updateSubscriber(ctx);
          }
        },
        delete: {
          params: {
            id: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.deleteSubscriber(ctx);
          }
        },
        addPushToken: {
          params: {
            subscriberId: "string",
            token: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.addPushToken(ctx);
          }
        },
        removePushToken: {
          params: {
            subscriberId: "string",
            token: "string"
          },
          async handler(ctx: Context): Promise<any> {
            const subscriberController = container.get("subscriberController");
            return subscriberController.removePushToken(ctx);
          }
        }
      }
    });
    
    console.log('Notification service broker initialized successfully');
  } catch (error) {
    console.error('Failed to initialize notification service broker:', error);
    process.exit(1);
  }
})();

export { broker };
