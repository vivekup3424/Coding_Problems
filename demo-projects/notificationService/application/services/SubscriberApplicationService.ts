import { SubscriberEntity } from "../../domain/entities/SubscriberEntity";
import type { ISubscriberRepository } from "../../domain/repositories/ISubscriberRepository";
import type { ITopicRepository } from "../../domain/repositories/ITopicRepository";

/**
 * Application service for managing subscribers
 */
export class SubscriberApplicationService {
  constructor(
    private subscriberRepository: ISubscriberRepository,
    private topicRepository: ITopicRepository
  ) {}

  /**
   * Create a new subscriber
   */
  async createSubscriber(data: { 
    firstName: string; 
    lastName: string; 
    email?: string; 
    phoneNumber?: string;
    pushTokens?: string[];
  }): Promise<SubscriberEntity> {
    const subscriber = new SubscriberEntity({
      firstName: data.firstName,
      lastName: data.lastName,
      email: data.email,
      phoneNumber: data.phoneNumber,
      pushTokens: data.pushTokens
    });
    
    await this.subscriberRepository.save(subscriber);
    return subscriber;
  }

  /**
   * Get a subscriber by ID
   */
  async getSubscriberById(id: string): Promise<SubscriberEntity | null> {
    return this.subscriberRepository.findById(id);
  }

  /**
   * List all subscribers
   */
  async listSubscribers(): Promise<SubscriberEntity[]> {
    return this.subscriberRepository.findAll();
  }

  /**
   * Update a subscriber
   */
  async updateSubscriber(
    id: string, 
    data: Partial<{ 
      firstName: string; 
      lastName: string; 
      email: string; 
      phoneNumber: string;
    }>
  ): Promise<SubscriberEntity | null> {
    const subscriber = await this.subscriberRepository.findById(id);
    if (!subscriber) return null;
    
    subscriber.update(data);
    await this.subscriberRepository.save(subscriber);
    return subscriber;
  }

  /**
   * Delete a subscriber
   */
  async deleteSubscriber(id: string): Promise<boolean> {
    return this.subscriberRepository.delete(id);
  }

  /**
   * Add a push token to a subscriber
   */
  async addPushToken(subscriberId: string, token: string): Promise<boolean> {
    const subscriber = await this.subscriberRepository.findById(subscriberId);
    if (!subscriber) return false;
    
    subscriber.addPushToken(token);
    await this.subscriberRepository.save(subscriber);
    return true;
  }

  /**
   * Remove a push token from a subscriber
   */
  async removePushToken(subscriberId: string, token: string): Promise<boolean> {
    const subscriber = await this.subscriberRepository.findById(subscriberId);
    if (!subscriber) return false;
    
    subscriber.removePushToken(token);
    await this.subscriberRepository.save(subscriber);
    return true;
  }

  /**
   * Get subscribers by topic ID
   */
  async getSubscribersByTopicId(topicId: string): Promise<SubscriberEntity[]> {
    return this.subscriberRepository.findByTopicId(topicId);
  }
}
