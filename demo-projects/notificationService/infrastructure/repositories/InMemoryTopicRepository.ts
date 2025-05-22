import { TopicEntity } from "../../domain/entities/TopicEntity";
import type { ITopicRepository } from "../../domain/repositories/ITopicRepository";

/**
 * In-memory implementation of the Topic repository
 */
export class InMemoryTopicRepository implements ITopicRepository {
  private topics = new Map<string, TopicEntity>();

  /**
   * Save a topic entity
   */
  async save(topic: TopicEntity): Promise<void> {
    this.topics.set(topic.id, topic);
  }

  /**
   * Find a topic by its ID
   */
  async findById(id: string): Promise<TopicEntity | null> {
    const topic = this.topics.get(id);
    return topic || null;
  }

  /**
   * Find all topics
   */
  async findAll(): Promise<TopicEntity[]> {
    return Array.from(this.topics.values());
  }

  /**
   * Delete a topic by its ID
   */
  async delete(id: string): Promise<boolean> {
    return this.topics.delete(id);
  }

  /**
   * Find topics by subscriber ID
   */
  async findBySubscriberId(subscriberId: string): Promise<TopicEntity[]> {
    return Array.from(this.topics.values())
      .filter(topic => topic.hasSubscriber(subscriberId));
  }
}
