import { ServiceBroker, Context } from "moleculer";
import type { IDomainEventPublisher, DomainEventHandler } from "../../domain/events/DomainEventPublisher";
import { DomainEvent } from "../../domain/events/DomainEvent";

/**
 * Adapter to bridge domain events with Moleculer events
 */
export class MoleculerEventAdapter implements IDomainEventPublisher {
  private broker: ServiceBroker;
  private eventPrefix: string;

  constructor(broker: ServiceBroker, eventPrefix: string = "domain") {
    this.broker = broker;
    this.eventPrefix = eventPrefix;
  }

  /**
   * Publish a domain event as a Moleculer event
   */
  async publish<T extends DomainEvent>(event: T): Promise<void> {
    const eventName = `${this.eventPrefix}.${event.eventName}`;
    await this.broker.emit(eventName, event);
  }

  /**
   * Subscribe to a domain event via Moleculer
   */
  subscribe<T extends DomainEvent>(eventName: string, handler: DomainEventHandler<T>): void {
    const moleculerEventName = `${this.eventPrefix}.${eventName}`;
    
    // Create a service to handle this event
    this.broker.createService({
      name: `event-handler-${eventName}`,
      events: {
        [moleculerEventName]: async (ctx: Context<T>) => {
          try {
            await handler.handle(ctx.params);
          } catch (error) {
            this.broker.logger.error(`Error handling event ${eventName}:`, error);
          }
        }
      }
    });
  }
}
