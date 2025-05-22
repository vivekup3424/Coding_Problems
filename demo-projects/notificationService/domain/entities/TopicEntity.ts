import { v4 as uuidv4 } from "uuid";

/**
 * Topic entity representing a notification topic in the domain
 */
export class TopicEntity {
  readonly id: string;
  private _name: string;
  private _description: string;
  private _subscriberIds: Set<string>;
  readonly createdAt: Date;
  private _updatedAt: Date;

  constructor(props: {
    id?: string;
    name: string;
    description?: string;
    subscriberIds?: string[];
    createdAt?: Date;
    updatedAt?: Date;
  }) {
    this.id = props.id || uuidv4();
    this._name = props.name;
    this._description = props.description || '';
    this._subscriberIds = new Set(props.subscriberIds || []);
    this.createdAt = props.createdAt || new Date();
    this._updatedAt = props.updatedAt || new Date();
  }

  /**
   * Get the topic name
   */
  get name(): string {
    return this._name;
  }

  /**
   * Get the topic description
   */
  get description(): string {
    return this._description;
  }

  /**
   * Get the subscriber IDs for this topic
   */
  get subscriberIds(): string[] {
    return Array.from(this._subscriberIds);
  }

  /**
   * Get the last updated timestamp
   */
  get updatedAt(): Date {
    return this._updatedAt;
  }

  /**
   * Update the topic information
   */
  update(data: Partial<{
    name: string;
    description: string;
  }>): void {
    if (data.name) this._name = data.name;
    if (data.description) this._description = data.description;
    this._updatedAt = new Date();
  }

  /**
   * Add a subscriber to the topic
   */
  addSubscriber(subscriberId: string): void {
    if (!this._subscriberIds.has(subscriberId)) {
      this._subscriberIds.add(subscriberId);
      this._updatedAt = new Date();
    }
  }

  /**
   * Remove a subscriber from the topic
   */
  removeSubscriber(subscriberId: string): void {
    if (this._subscriberIds.has(subscriberId)) {
      this._subscriberIds.delete(subscriberId);
      this._updatedAt = new Date();
    }
  }

  /**
   * Check if a subscriber is subscribed to this topic
   */
  hasSubscriber(subscriberId: string): boolean {
    return this._subscriberIds.has(subscriberId);
  }

  /**
   * Convert entity to a plain object for persistence
   */
  toJSON() {
    return {
      id: this.id,
      name: this._name,
      description: this._description,
      subscriberIds: Array.from(this._subscriberIds),
      createdAt: this.createdAt,
      updatedAt: this._updatedAt
    };
  }

  /**
   * Create a TopicEntity from a plain object
   */
  static fromJSON(data: any): TopicEntity {
    return new TopicEntity({
      id: data.id,
      name: data.name,
      description: data.description,
      subscriberIds: data.subscriberIds,
      createdAt: new Date(data.createdAt),
      updatedAt: new Date(data.updatedAt)
    });
  }
}
