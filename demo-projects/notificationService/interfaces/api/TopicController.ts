import type { TopicApplicationService } from "../../application/services/TopicApplicationService";

/**
 * Controller for handling topic-related API endpoints
 */
export class TopicController {
  constructor(private topicService: TopicApplicationService) {}

  /**
   * Create a new topic
   */
  async createTopic(req: any): Promise<any> {
    const { name, description } = req.body;
    const topic = await this.topicService.createTopic({ name, description });
    return { success: true, topic: topic.toJSON() };
  }

  /**
   * Get a topic by ID
   */
  async getTopic(req: any): Promise<any> {
    const id = req.params.id;
    const topic = await this.topicService.getTopicById(id);
    
    if (!topic) {
      return { success: false, message: "Topic not found" };
    }
    
    return { success: true, topic: topic.toJSON() };
  }

  /**
   * List all topics
   */
  async listTopics(): Promise<any> {
    const topics = await this.topicService.listTopics();
    return { 
      success: true, 
      topics: topics.map(topic => topic.toJSON()) 
    };
  }

  /**
   * Update a topic
   */
  async updateTopic(req: any): Promise<any> {
    const id = req.params.id;
    const { name, description } = req.body;
    
    const topic = await this.topicService.updateTopic(id, { name, description });
    
    if (!topic) {
      return { success: false, message: "Topic not found" };
    }
    
    return { success: true, topic: topic.toJSON() };
  }

  /**
   * Delete a topic
   */
  async deleteTopic(req: any): Promise<any> {
    const id = req.params.id;
    const success = await this.topicService.deleteTopic(id);
    
    if (!success) {
      return { success: false, message: "Topic not found or could not be deleted" };
    }
    
    return { success: true };
  }

  /**
   * Subscribe a user to a topic
   */
  async subscribeTopic(req: any): Promise<any> {
    const { topicId, subscriberId } = req.body;
    
    const success = await this.topicService.addSubscriberToTopic(topicId, subscriberId);
    
    if (!success) {
      return { 
        success: false, 
        message: "Failed to subscribe: Topic or subscriber not found" 
      };
    }
    
    return { success: true };
  }

  /**
   * Unsubscribe a user from a topic
   */
  async unsubscribeTopic(req: any): Promise<any> {
    const { topicId, subscriberId } = req.body;
    
    const success = await this.topicService.removeSubscriberFromTopic(topicId, subscriberId);
    
    if (!success) {
      return { 
        success: false, 
        message: "Failed to unsubscribe: Topic not found or subscriber not subscribed" 
      };
    }
    
    return { success: true };
  }
}
