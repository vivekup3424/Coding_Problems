import { TopicEntity } from "../../domain/entities/TopicEntity";
import type { ITopicRepository } from "../../domain/repositories/ITopicRepository";
import type { ISubscriberRepository } from "../../domain/repositories/ISubscriberRepository";

export class TopicApplicationService {
  constructor(
    private topicRepository: ITopicRepository,
    private subscriberRepository: ISubscriberRepository
  ) {}

  async createTopic(data: { name: string; description?: string }): Promise<TopicEntity> {
    const topic = new TopicEntity({
      name: data.name,
      description: data.description
    });
    
    await this.topicRepository.save(topic);
    return topic;
  }

  async getTopicById(id: string): Promise<TopicEntity | null> {
    return this.topicRepository.findById(id);
  }

  async listTopics(): Promise<TopicEntity[]> {
    return this.topicRepository.findAll();
  }

  async updateTopic(
    id: string, 
    data: Partial<{ name: string; description: string }>
  ): Promise<TopicEntity | null> {
    const topic = await this.topicRepository.findById(id);
    if (!topic) return null;
    
    topic.update(data);
    await this.topicRepository.save(topic);
    return topic;
  }

  async deleteTopic(id: string): Promise<boolean> {
    return this.topicRepository.delete(id);
  }

  async addSubscriberToTopic(topicId: string, subscriberId: string): Promise<boolean> {
    const [topic, subscriber] = await Promise.all([
      this.topicRepository.findById(topicId),
      this.subscriberRepository.findById(subscriberId)
    ]);

    if (!topic || !subscriber) return false;
    
    topic.addSubscriber(subscriberId);
    await this.topicRepository.save(topic);
    return true;
  }

  /**
   * Remove a subscriber from a topic
   */
  async removeSubscriberFromTopic(topicId: string, subscriberId: string): Promise<boolean> {
    const topic = await this.topicRepository.findById(topicId);
    if (!topic) return false;
    
    topic.removeSubscriber(subscriberId);
    await this.topicRepository.save(topic);
    return true;
  }

  /**
   * Get topics by subscriber ID
   */
  async getTopicsBySubscriberId(subscriberId: string): Promise<TopicEntity[]> {
    return this.topicRepository.findBySubscriberId(subscriberId);
  }
}
