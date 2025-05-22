import { v4 as uuidv4 } from "uuid";

/**
 * Subscriber entity representing a subscriber in the domain
 */
export class SubscriberEntity {
  readonly id: string;
  private _firstName: string;
  private _lastName: string;
  private _email: string;
  private _phoneNumber: string;
  private _pushTokens: string[];
  readonly createdAt: Date;
  private _updatedAt: Date;

  constructor(props: {
    id?: string;
    firstName: string;
    lastName: string;
    email?: string;
    phoneNumber?: string;
    pushTokens?: string[];
    createdAt?: Date;
    updatedAt?: Date;
  }) {
    this.id = props.id || uuidv4();
    this._firstName = props.firstName;
    this._lastName = props.lastName;
    this._email = props.email || '';
    this._phoneNumber = props.phoneNumber || '';
    this._pushTokens = props.pushTokens || [];
    this.createdAt = props.createdAt || new Date();
    this._updatedAt = props.updatedAt || new Date();
  }

  /**
   * Get the subscriber's first name
   */
  get firstName(): string {
    return this._firstName;
  }

  /**
   * Get the subscriber's last name
   */
  get lastName(): string {
    return this._lastName;
  }

  /**
   * Get the subscriber's full name
   */
  get fullName(): string {
    return `${this._firstName} ${this._lastName}`;
  }

  /**
   * Get the subscriber's email
   */
  get email(): string {
    return this._email;
  }

  /**
   * Get the subscriber's phone number
   */
  get phoneNumber(): string {
    return this._phoneNumber;
  }

  /**
   * Get the subscriber's push tokens
   */
  get pushTokens(): string[] {
    return [...this._pushTokens];
  }

  /**
   * Get the last updated timestamp
   */
  get updatedAt(): Date {
    return this._updatedAt;
  }

  /**
   * Update the subscriber's information
   */
  update(data: Partial<{
    firstName: string;
    lastName: string;
    email: string;
    phoneNumber: string;
  }>): void {
    if (data.firstName) this._firstName = data.firstName;
    if (data.lastName) this._lastName = data.lastName;
    if (data.email) this._email = data.email;
    if (data.phoneNumber) this._phoneNumber = data.phoneNumber;
    this._updatedAt = new Date();
  }

  /**
   * Add a push token for the subscriber
   */
  addPushToken(token: string): void {
    if (!this._pushTokens.includes(token)) {
      this._pushTokens.push(token);
      this._updatedAt = new Date();
    }
  }

  /**
   * Remove a push token from the subscriber
   */
  removePushToken(token: string): void {
    const index = this._pushTokens.indexOf(token);
    if (index !== -1) {
      this._pushTokens.splice(index, 1);
      this._updatedAt = new Date();
    }
  }

  /**
   * Convert entity to a plain object for persistence
   */
  toJSON() {
    return {
      id: this.id,
      firstName: this._firstName,
      lastName: this._lastName,
      email: this._email,
      phoneNumber: this._phoneNumber,
      pushTokens: this._pushTokens,
      createdAt: this.createdAt,
      updatedAt: this._updatedAt
    };
  }

  /**
   * Create a SubscriberEntity from a plain object
   */
  static fromJSON(data: any): SubscriberEntity {
    return new SubscriberEntity({
      id: data.id,
      firstName: data.firstName,
      lastName: data.lastName,
      email: data.email,
      phoneNumber: data.phoneNumber,
      pushTokens: data.pushTokens,
      createdAt: new Date(data.createdAt),
      updatedAt: new Date(data.updatedAt)
    });
  }
}
