export abstract class DomainEvent {
  readonly occurredOn: Date;
  
  constructor() {
    this.occurredOn = new Date();
  }
  
  abstract get eventName(): string;
}

export class NotificationCreatedEvent extends DomainEvent {
  constructor(
    readonly notificationId: string, 
    readonly subscriberId: string | undefined,
    readonly topicId: string | undefined,
    readonly provider: string
  ) {
    super();
  }
  
  get eventName(): string {
    return 'notification.created';
  }
}

export class NotificationSentEvent extends DomainEvent {
  constructor(
    readonly notificationId: string, 
    readonly subscriberId: string | undefined,
    readonly provider: string
  ) {
    super();
  }
  
  get eventName(): string {
    return 'notification.sent';
  }
}

export class NotificationFailedEvent extends DomainEvent {
  constructor(
    readonly notificationId: string, 
    readonly subscriberId: string | undefined,
    readonly provider: string,
    readonly reason: string
  ) {
    super();
  }
  
  get eventName(): string {
    return 'notification.failed';
  }
}

export class NotificationReadEvent extends DomainEvent {
  constructor(
    readonly notificationId: string, 
    readonly subscriberId: string | undefined,
    readonly deviceId: string | undefined,
    readonly readAt: Date
  ) {
    super();
  }
  
  get eventName(): string {
    return 'notification.read';
  }
}
