import type { SubscriberApplicationService } from "../../application/services/SubscriberApplicationService";

/**
 * Controller for handling subscriber-related API endpoints
 */
export class SubscriberController {
  constructor(private subscriberService: SubscriberApplicationService) {}

  /**
   * Create a new subscriber
   */
  async createSubscriber(req: any): Promise<any> {
    const { firstName, lastName, email, phoneNumber, pushTokens } = req.body;
    
    const subscriber = await this.subscriberService.createSubscriber({
      firstName,
      lastName,
      email,
      phoneNumber,
      pushTokens
    });
    
    return { success: true, subscriber: subscriber.toJSON() };
  }

  /**
   * Get a subscriber by ID
   */
  async getSubscriber(req: any): Promise<any> {
    const id = req.params.id;
    const subscriber = await this.subscriberService.getSubscriberById(id);
    
    if (!subscriber) {
      return { success: false, message: "Subscriber not found" };
    }
    
    return { success: true, subscriber: subscriber.toJSON() };
  }

  /**
   * List all subscribers
   */
  async listSubscribers(): Promise<any> {
    const subscribers = await this.subscriberService.listSubscribers();
    return { 
      success: true, 
      subscribers: subscribers.map(subscriber => subscriber.toJSON()) 
    };
  }

  /**
   * Update a subscriber
   */
  async updateSubscriber(req: any): Promise<any> {
    const id = req.params.id;
    const { firstName, lastName, email, phoneNumber } = req.body;
    
    const subscriber = await this.subscriberService.updateSubscriber(id, {
      firstName,
      lastName,
      email,
      phoneNumber
    });
    
    if (!subscriber) {
      return { success: false, message: "Subscriber not found" };
    }
    
    return { success: true, subscriber: subscriber.toJSON() };
  }

  /**
   * Delete a subscriber
   */
  async deleteSubscriber(req: any): Promise<any> {
    const id = req.params.id;
    const success = await this.subscriberService.deleteSubscriber(id);
    
    if (!success) {
      return { success: false, message: "Subscriber not found or could not be deleted" };
    }
    
    return { success: true };
  }

  /**
   * Add a push token to a subscriber
   */
  async addPushToken(req: any): Promise<any> {
    const { subscriberId, token } = req.body;
    
    const success = await this.subscriberService.addPushToken(subscriberId, token);
    
    if (!success) {
      return { success: false, message: "Subscriber not found" };
    }
    
    return { success: true };
  }

  /**
   * Remove a push token from a subscriber
   */
  async removePushToken(req: any): Promise<any> {
    const { subscriberId, token } = req.body;
    
    const success = await this.subscriberService.removePushToken(subscriberId, token);
    
    if (!success) {
      return { success: false, message: "Subscriber not found or token doesn't exist" };
    }
    
    return { success: true };
  }
}
