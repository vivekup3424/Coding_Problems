import type { ISubscriberRepository } from "../../domain/repositories/ISubscriberRepository";
import { SubscriberEntity } from "../../domain/entities/SubscriberEntity";
import { SubscriberModel } from "../database/schemas/SubscriberSchema";

/**
 * MongoDB implementation of the subscriber repository
 */
export class MongoSubscriberRepository implements ISubscriberRepository {
  
  /**
   * Save a subscriber entity to MongoDB
   */
  async save(subscriber: SubscriberEntity): Promise<void> {
    const data = subscriber.toJSON();
    
    await SubscriberModel.findOneAndUpdate(
      { id: subscriber.id },
      data,
      { upsert: true, new: true }
    );
  }
  
  /**
   * Find a subscriber by ID from MongoDB
   */
  async findById(id: string): Promise<SubscriberEntity | null> {
    const subscriber = await SubscriberModel.findOne({ id }).lean();
    return subscriber ? SubscriberEntity.fromJSON(subscriber) : null;
  }
  
  /**
   * Find all subscribers from MongoDB
   */
  async findAll(): Promise<SubscriberEntity[]> {
    const subscribers = await SubscriberModel.find().lean();
    return subscribers.map(data => SubscriberEntity.fromJSON(data));
  }
  
  /**
   * Delete a subscriber by ID from MongoDB
   */
  async delete(id: string): Promise<boolean> {
    const result = await SubscriberModel.deleteOne({ id });
    return result.deletedCount > 0;
  }
  
  /**
   * Find subscribers by topic ID from MongoDB
   */
  async findByTopicId(topicId: string): Promise<SubscriberEntity[]> {
    const subscribers = await SubscriberModel.find({ 
      topics: topicId 
    }).lean();
    
    return subscribers.map(data => SubscriberEntity.fromJSON(data));
  }
}
