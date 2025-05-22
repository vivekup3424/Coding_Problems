import { SubscriberEntity } from "../../domain/entities/SubscriberEntity";
import type { ISubscriberRepository } from "../../domain/repositories/ISubscriberRepository";

/**
 * In-memory implementation of the Subscriber repository
 */
export class InMemorySubscriberRepository implements ISubscriberRepository {
  private subscribers = new Map<string, SubscriberEntity>();
  private topicSubscribers = new Map<string, Set<string>>();

  /**
   * Save a subscriber entity
   */
  async save(subscriber: SubscriberEntity): Promise<void> {
    this.subscribers.set(subscriber.id, subscriber);
  }

  /**
   * Find a subscriber by its ID
   */
  async findById(id: string): Promise<SubscriberEntity | null> {
    const subscriber = this.subscribers.get(id);
    return subscriber || null;
  }

  /**
   * Find all subscribers
   */
  async findAll(): Promise<SubscriberEntity[]> {
    return Array.from(this.subscribers.values());
  }

  /**
   * Delete a subscriber by its ID
   */
  async delete(id: string): Promise<boolean> {
    // Also clean up any topic-subscriber relationships
    for (const [topicId, subscriberIds] of this.topicSubscribers.entries()) {
      subscriberIds.delete(id);
    }
    return this.subscribers.delete(id);
  }

  /**
   * Find subscribers by topic ID
   */
  async findByTopicId(topicId: string): Promise<SubscriberEntity[]> {
    const subscriberIds = this.topicSubscribers.get(topicId);
    if (!subscriberIds) return [];
    
    return Array.from(subscriberIds)
      .map(id => this.subscribers.get(id))
      .filter((subscriber): subscriber is SubscriberEntity => subscriber !== undefined);
  }

  /**
   * Add a topic-subscriber relation
   * Note: This is an infrastructure-specific method to maintain the relation
   * for efficient lookups
   */
  setTopicSubscriberRelation(topicId: string, subscriberId: string): void {
    if (!this.topicSubscribers.has(topicId)) {
      this.topicSubscribers.set(topicId, new Set<string>());
    }
    this.topicSubscribers.get(topicId)?.add(subscriberId);
  }

  /**
   * Remove a topic-subscriber relation
   */
  removeTopicSubscriberRelation(topicId: string, subscriberId: string): void {
    const subscriberIds = this.topicSubscribers.get(topicId);
    if (subscriberIds) {
      subscriberIds.delete(subscriberId);
    }
  }
}
