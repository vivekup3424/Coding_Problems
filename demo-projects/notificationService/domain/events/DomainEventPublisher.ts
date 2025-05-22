import { DomainEvent } from "./DomainEvent";

/**
 * Interface for handling domain events
 */
export interface DomainEventHandler<T extends DomainEvent> {
  handle(event: T): Promise<void>;
}

/**
 * Domain event publisher interface
 */
export interface IDomainEventPublisher {
  publish<T extends DomainEvent>(event: T): Promise<void>;
  subscribe<T extends DomainEvent>(eventName: string, handler: DomainEventHandler<T>): void;
}

/**
 * In-memory implementation of a domain event publisher
 */
export class InMemoryDomainEventPublisher implements IDomainEventPublisher {
  private handlers: Map<string, DomainEventHandler<any>[]> = new Map();
  
  async publish<T extends DomainEvent>(event: T): Promise<void> {
    const eventHandlers = this.handlers.get(event.eventName) || [];
    
    for (const handler of eventHandlers) {
      try {
        await handler.handle(event);
      } catch (error) {
        console.error(`Error handling domain event ${event.eventName}:`, error);
      }
    }
  }
  
  subscribe<T extends DomainEvent>(eventName: string, handler: DomainEventHandler<T>): void {
    const handlers = this.handlers.get(eventName) || [];
    handlers.push(handler);
    this.handlers.set(eventName, handlers);
  }
}
