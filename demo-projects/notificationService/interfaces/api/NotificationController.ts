/**
 * Controller for notification-related API endpoints
 * Acts as an interface adapter in Clean Architecture
 */
import { ServiceBroker, Context } from "moleculer";
import type { SendNotificationUseCase, SendNotificationInput } from "../../application/useCases/SendNotificationUseCase";
import type { MarkNotificationAsReadUseCase } from "../../application/useCases/MarkNotificationAsReadUseCase";
import { NotificationApplicationService } from "../../application/services/NotificationApplicationService";
import type { TemplateContext } from "../../models/template";
import { Criticality } from "../../models/notification";
import type { INotificationRepository } from "../../domain/repositories/INotificationRepository";
import type { ITemplateRepository } from "../../domain/repositories/ITemplateRepository";

// Define types for API requests
interface SendNotificationRequest {
  templateId: string;
  subscriberId?: string;
  topicId?: string;
  provider: "sms" | "push" | "email";
  payload: Record<string, any>;
  templateContext?: Record<string, any>;
  criticality: string;
}

interface MarkAsReadRequest {
  notificationId: string;
  deviceId?: string;
  clientTimestamp?: number;
  clientData?: Record<string, any>;
}

interface SubscriberRequest {
  subscriberId: string;
}

/**
 * Controller for notification-related API endpoints
 */
export class NotificationController {
  private notificationService: NotificationApplicationService;
  
  constructor(
    private broker: ServiceBroker,
    private sendNotificationUseCase: SendNotificationUseCase,
    private markAsReadUseCase: MarkNotificationAsReadUseCase,
    private notificationRepository: INotificationRepository,
    private templateRepository: ITemplateRepository
  ) {
    // Create application service with use cases
    this.notificationService = new NotificationApplicationService(
      sendNotificationUseCase,
      markAsReadUseCase,
      notificationRepository,
      templateRepository
    );
    
    this.registerActions();
  }

  private registerActions() {
    this.broker.createService({
      name: "notification-api",
      actions: {
        // Create and send a notification
        send: {
          params: {
            templateId: "string",
            subscriberId: { type: "string", optional: true },
            topicId: { type: "string", optional: true },
            provider: { type: "string", enum: ["sms", "push", "email"] },
            payload: "object",
            templateContext: { type: "object", optional: true },
            criticality: { type: "string", enum: ["HIGH", "MEDIUM", "LOW"] }
          },
          handler: async (ctx: Context<SendNotificationRequest>) => {
            const params = ctx.params;
            
            // Validate that either subscriberId or topicId is provided
            if (!params.subscriberId && !params.topicId) {
              throw new Error("Either subscriberId or topicId must be provided");
            }
            
            // Get subscriber IDs based on input
            let subscriberIds: string[] = [];
            if (params.subscriberId) {
              subscriberIds = [params.subscriberId];
            } else if (params.topicId) {
              try {
                // In a real implementation, we'd fetch subscribers from a topic service
                // This is simplified for demo purposes
                subscriberIds = await ctx.call("topic.getSubscribers", { topicId: params.topicId });
              } catch (error) {
                // For demo purposes, if topic service is not available
                console.warn("Topic service unavailable, using demo subscriber ID");
                subscriberIds = ["demo-subscriber-1"];
              }
            }
            
            // Create and send notifications
            return this.notificationService.createAndSendNotification({
              templateId: params.templateId,
              subscriberId: params.subscriberId,
              topicId: params.topicId,
              provider: params.provider as "sms" | "push" | "email",
              payload: params.payload,
              templateContext: params.templateContext as TemplateContext | undefined,
              criticality: params.criticality as Criticality
            }, subscriberIds);
          }
        },
        
        // Mark a notification as read
        markAsRead: {
          params: {
            notificationId: "string",
            deviceId: { type: "string", optional: true },
            clientTimestamp: { type: "number", optional: true },
            clientData: { type: "object", optional: true }
          },
          handler: async (ctx: Context<MarkAsReadRequest>) => {
            const { notificationId, deviceId, clientTimestamp, clientData = {} } = ctx.params;
            
            // Prepare client data
            const clientMetadata = { ...clientData };
            if (deviceId) clientMetadata.deviceId = deviceId;
            if (clientTimestamp) clientMetadata.clientTimestamp = clientTimestamp;
            
            return this.notificationService.markNotificationAsRead(notificationId, clientMetadata);
          }
        },
        
        // Get unread notifications for a subscriber
        getUnreadNotifications: {
          params: {
            subscriberId: "string"
          },
          handler: async (ctx: Context<SubscriberRequest>) => {
            return this.notificationService.getUnreadNotificationsForSubscriber(ctx.params.subscriberId);
          }
        },
        
        // Get all notifications for a subscriber
        getNotifications: {
          params: {
            subscriberId: "string"
          },
          handler: async (ctx: Context<SubscriberRequest>) => {
            return this.notificationService.getNotificationsForSubscriber(ctx.params.subscriberId);
          }
        }
      }
    });
  }
}
