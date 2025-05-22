import type { ITopicRepository } from "../../domain/repositories/ITopicRepository";
import { TopicEntity } from "../../domain/entities/TopicEntity";
import { TopicModel } from "../database/schemas/TopicSchema";

/**
 * MongoDB implementation of the topic repository
 */
export class MongoTopicRepository implements ITopicRepository {
  
  /**
   * Save a topic entity to MongoDB
   */
  async save(topic: TopicEntity): Promise<void> {
    const data = topic.toJSON();
    
    await TopicModel.findOneAndUpdate(
      { id: topic.id },
      data,
      { upsert: true, new: true }
    );
  }
  
  /**
   * Find a topic by ID from MongoDB
   */
  async findById(id: string): Promise<TopicEntity | null> {
    const topic = await TopicModel.findOne({ id }).lean();
    return topic ? TopicEntity.fromJSON(topic) : null;
  }
  
  /**
   * Find all topics from MongoDB
   */
  async findAll(): Promise<TopicEntity[]> {
    const topics = await TopicModel.find().lean();
    return topics.map(data => TopicEntity.fromJSON(data));
  }
  
  /**
   * Delete a topic by ID from MongoDB
   */
  async delete(id: string): Promise<boolean> {
    const result = await TopicModel.deleteOne({ id });
    return result.deletedCount > 0;
  }
  
  /**
   * Find topics by subscriber ID from MongoDB
   */
  async findBySubscriberId(subscriberId: string): Promise<TopicEntity[]> {
    const topics = await TopicModel.find({ 
      subscribers: subscriberId 
    }).lean();
    
    return topics.map(data => TopicEntity.fromJSON(data));
  }
}
