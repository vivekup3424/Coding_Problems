import { TopicEntity } from "../entities/TopicEntity";

/**
 * Repository interface for Topic domain entities
 */
export interface ITopicRepository {
  /**
   * Save a topic entity
   */
  save(topic: TopicEntity): Promise<void>;

  /**
   * Find a topic by its ID
   */
  findById(id: string): Promise<TopicEntity | null>;

  /**
   * Find all topics
   */
  findAll(): Promise<TopicEntity[]>;

  /**
   * Delete a topic by its ID
   */
  delete(id: string): Promise<boolean>;

  /**
   * Find topics by subscriber ID
   */
  findBySubscriberId(subscriberId: string): Promise<TopicEntity[]>;
}
