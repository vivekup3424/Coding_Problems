/**
 * Value object representing the content of a notification
 * Encapsulates the provider-specific content structure
 */
export class NotificationContent {
  private readonly _data: Record<string, any>;
  private readonly _provider: "sms" | "push" | "email";

  constructor(provider: "sms" | "push" | "email", data: Record<string, any>) {
    this._provider = provider;
    this._data = this.validateContent(provider, data);
  }

  /**
   * Validate that the content has the required fields for the provider
   */
  private validateContent(provider: string, data: Record<string, any>): Record<string, any> {
    if (provider === "sms" && !data.to) {
      throw new Error("SMS notification requires 'to' field");
    }

    if (provider === "email") {
      if (!data.to) throw new Error("Email notification requires 'to' field");
      if (!data.subject && !data.title) throw new Error("Email notification requires 'subject' or 'title' field");
    }

    if (provider === "push" && !data.token) {
      throw new Error("Push notification requires 'token' field");
    }

    return { ...data };
  }

  /**
   * Get the raw data
   */
  get data(): Record<string, any> {
    return { ...this._data };
  }
  
  /**
   * Get the payload data
   */
  getPayload(): Record<string, any> {
    return { ...this._data };
  }

  /**
   * Get the provider type
   */
  get provider(): "sms" | "push" | "email" {
    return this._provider;
  }

  /**
   * Set message content for the notification
   */
  withMessage(message: string): NotificationContent {
    const updatedData = { ...this._data };
    
    if (this._provider === "sms") {
      updatedData.message = message;
    } else if (this._provider === "email") {
      updatedData.body = message;
    } else if (this._provider === "push") {
      updatedData.body = message;
    }
    
    return new NotificationContent(this._provider, updatedData);
  }

  /**
   * Set title for push or email notifications
   */
  withTitle(title: string): NotificationContent {
    if (this._provider === "sms") {
      return this; // SMS doesn't use titles
    }
    
    const updatedData = { ...this._data };
    
    if (this._provider === "email") {
      updatedData.subject = title;
    } else if (this._provider === "push") {
      updatedData.title = title;
    }
    
    return new NotificationContent(this._provider, updatedData);
  }

  /**
   * Equality comparison with another NotificationContent
   */
  equals(other: NotificationContent): boolean {
    if (this._provider !== other._provider) return false;
    
    const thisKeys = Object.keys(this._data);
    const otherKeys = Object.keys(other._data);
    
    if (thisKeys.length !== otherKeys.length) return false;
    
    for (const key of thisKeys) {
      if (this._data[key] !== other._data[key]) return false;
    }
    
    return true;
  }

  /**
   * Convert to plain object
   */
  toJSON() {
    return {
      provider: this._provider,
      data: this._data
    };
  }
}
