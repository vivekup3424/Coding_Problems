import { v4 as uuidv4 } from "uuid";
import { NotificationStatus, Criticality, type Notification } from "../../models/notification";

/**
 * Notification entity representing a notification in the domain
 */
export class NotificationEntity {
  readonly id: string;
  readonly templateId: string;
  readonly subscriberId?: string;
  readonly topicId?: string;
  readonly provider: "sms" | "push" | "email";
  readonly payload: Record<string, any>;
  private _status: NotificationStatus;
  readonly criticality: Criticality;
  readonly createdAt: Date;
  private _updatedAt: Date;
  private _readAt?: Date;
  private _clientData?: {
    deviceId?: string;
    readReceipt?: boolean;
    clientTimestamp?: number;
    [key: string]: any;
  };

  constructor(props: {
    id?: string;
    templateId: string;
    subscriberId?: string;
    topicId?: string;
    provider: "sms" | "push" | "email";
    payload: Record<string, any>;
    status?: NotificationStatus;
    criticality: Criticality;
    createdAt?: Date;
    updatedAt?: Date;
    readAt?: Date;
    clientData?: {
      deviceId?: string;
      readReceipt?: boolean;
      clientTimestamp?: number;
      [key: string]: any;
    };
  }) {
    this.id = props.id || uuidv4();
    this.templateId = props.templateId;
    this.subscriberId = props.subscriberId;
    this.topicId = props.topicId;
    this.provider = props.provider;
    this.payload = props.payload;
    this._status = props.status || NotificationStatus.Pending;
    this.criticality = props.criticality;
    this.createdAt = props.createdAt || new Date();
    this._updatedAt = props.updatedAt || new Date();
    this._readAt = props.readAt;
    this._clientData = props.clientData;
  }

  /**
   * Get the current status of the notification
   */
  get status(): NotificationStatus {
    return this._status;
  }

  /**
   * Get the last updated timestamp
   */
  get updatedAt(): Date {
    return this._updatedAt;
  }

  /**
   * Get the timestamp when the notification was read
   */
  get readAt(): Date | undefined {
    return this._readAt;
  }

  /**
   * Get client data associated with this notification
   */
  get clientData(): Record<string, any> | undefined {
    return this._clientData;
  }

  /**
   * Mark the notification as sent
   */
  markAsSent(): void {
    this._status = NotificationStatus.Sent;
    this._updatedAt = new Date();
  }

  /**
   * Mark the notification as acknowledged
   */
  acknowledge(): void {
    this._status = NotificationStatus.Acknowledged;
    this._updatedAt = new Date();
  }

  /**
   * Mark the notification as read
   */
  markAsRead(clientData?: Record<string, any>): void {
    this._status = NotificationStatus.Read;
    this._readAt = new Date();
    this._updatedAt = new Date();

    if (clientData) {
      this._clientData = {
        ...this._clientData,
        ...clientData,
        readReceipt: true
      };
    }
  }

  /**
   * Mark the notification as failed
   */
  markAsFailed(): void {
    this._status = NotificationStatus.Failed;
    this._updatedAt = new Date();
  }

  /**
   * Convert entity to a plain object for persistence
   */
  toJSON() {
    return {
      id: this.id,
      templateId: this.templateId,
      subscriberId: this.subscriberId,
      topicId: this.topicId,
      provider: this.provider,
      payload: this.payload,
      status: this._status,
      criticality: this.criticality,
      createdAt: this.createdAt,
      updatedAt: this._updatedAt,
      readAt: this._readAt,
      clientData: this._clientData
    };
  }

  /**
   * Create a NotificationEntity from a plain object
   */
  static fromJSON(data: any): NotificationEntity {
    return new NotificationEntity({
      id: data.id,
      templateId: data.templateId,
      subscriberId: data.subscriberId,
      topicId: data.topicId,
      provider: data.provider,
      payload: data.payload,
      status: data.status,
      criticality: data.criticality,
      createdAt: new Date(data.createdAt),
      updatedAt: new Date(data.updatedAt),
      readAt: data.readAt ? new Date(data.readAt) : undefined,
      clientData: data.clientData
    });
  }
  
  /**
   * Create a NotificationEntity from a legacy Notification model
   */
  static createFromLegacy(notification: Notification): NotificationEntity {
    return new NotificationEntity({
      id: notification.id,
      templateId: notification.templateId,
      subscriberId: notification.subscriberId,
      topicId: notification.topicId,
      provider: notification.provider,
      payload: notification.payload,
      status: notification.status,
      criticality: notification.criticality,
      createdAt: new Date(notification.createdAt),
      updatedAt: new Date(notification.updatedAt),
      readAt: notification.readAt ? new Date(notification.readAt) : undefined,
      clientData: notification.clientData
    });
  }
}
