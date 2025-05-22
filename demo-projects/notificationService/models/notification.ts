export enum NotificationStatus {
  Pending = "PENDING",
  Sent = "SENT",
  Acknowledged = "ACKNOWLEDGED",
  Failed = "FAILED",
  Read = "READ"
}

export enum Criticality {
  High = "HIGH",
  Medium = "MEDIUM",
  Low = "LOW"
}

export interface Notification {
  id: string;
  templateId: string;
  subscriberId?: string;
  topicId?: string;
  provider: "sms" | "push" | "email";
  payload: Record<string, any>;
  status: NotificationStatus;
  criticality: Criticality;
  createdAt: Date;
  updatedAt: Date;
  readAt?: Date;
  clientData?: {
    deviceId?: string;
    readReceipt?: boolean;
    clientTimestamp?: number;
    [key: string]: any;
  };
}
