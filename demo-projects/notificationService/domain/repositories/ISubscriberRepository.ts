import { SubscriberEntity } from "../entities/SubscriberEntity";

/**
 * Repository interface for Subscriber domain entities
 */
export interface ISubscriberRepository {
  /**
   * Save a subscriber entity
   */
  save(subscriber: SubscriberEntity): Promise<void>;

  /**
   * Find a subscriber by its ID
   */
  findById(id: string): Promise<SubscriberEntity | null>;

  /**
   * Find all subscribers
   */
  findAll(): Promise<SubscriberEntity[]>;

  /**
   * Delete a subscriber by its ID
   */
  delete(id: string): Promise<boolean>;

  /**
   * Find subscribers by topic ID
   */
  findByTopicId(topicId: string): Promise<SubscriberEntity[]>;
}
