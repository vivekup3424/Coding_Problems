/**
 * Example script to demonstrate repository functionality
 * Can work with both MongoDB and in-memory repositories
 */
import { bootstrap } from './infrastructure/bootstrap';
import { NotificationStatus, Criticality } from './models/notification';
import { NotificationEntity } from './domain/entities/NotificationEntity';
import { SubscriberEntity } from './domain/entities/SubscriberEntity';
import { TemplateEntity } from './domain/entities/TemplateEntity';
import { TopicEntity } from './domain/entities/TopicEntity';
import { SERVICE_IDENTIFIERS } from './infrastructure/bootstrap';
import 'dotenv/config';
import type { INotificationRepository } from './domain/repositories/INotificationRepository';
import type { ISubscriberRepository } from './domain/repositories/ISubscriberRepository';
import type { ITemplateRepository } from './domain/repositories/ITemplateRepository';
import type { ITopicRepository } from './domain/repositories/ITopicRepository';

/**
 * Run the example with specified repository type
 */
async function run() {
  try {
    console.log('Starting the repository example...');
    
    // Parse command line arguments
    const useInMemory = process.argv.includes('--in-memory');
    if (useInMemory) {
      process.env.USE_IN_MEMORY_DB = 'true';
      console.log('Using in-memory repositories (--in-memory flag detected)');
    } else {
      console.log('MongoDB URI:', process.env.MONGODB_URI || 'mongodb://localhost:27017/notification-service');
      console.log('Attempting to use MongoDB repositories...');
    }
    
    // Bootstrap application with minimal config (actual values are loaded from .env)
    const { container } = await bootstrap({
      smsConfig: { accessToken: "fake-token" },
      pushConfig: { 
        firebaseConfig: {
          apiKey: "fake-api-key",
          authDomain: "example.com",
          projectId: "fake-project-id",
          appId: "fake-app-id"
        }
      },
      emailConfig: { 
        transportOptions: {
          host: "smtp.example.com",
          port: 587,
          secure: false,
          auth: {
            user: "fake@example.com",
            pass: "fake-password"
          }
        } 
      },
      mediumRetryCount: 3
    });
    
    // Access repositories through the container
    const notificationRepo = container.get<INotificationRepository>(SERVICE_IDENTIFIERS.NotificationRepository);
    const subscriberRepo = container.get<ISubscriberRepository>(SERVICE_IDENTIFIERS.SubscriberRepository);
    const templateRepo = container.get<ITemplateRepository>(SERVICE_IDENTIFIERS.TemplateRepository);
    const topicRepo = container.get<ITopicRepository>(SERVICE_IDENTIFIERS.TopicRepository);
    
    // Create a sample subscriber
    const subscriber = new SubscriberEntity({
      firstName: 'John',
      lastName: 'Doe',
      email: 'john.doe@example.com',
      phoneNumber: '+1234567890'
    });
    
    // Create a sample template (only use properties defined in the class)
    const template = new TemplateEntity({
      name: 'Welcome Email',
      content: 'Hello {{name}}, welcome to our service!',
      parameters: ['name']
    });
    
    // Create a sample topic
    const topic = new TopicEntity({
      name: 'System Notifications'
    });
    
    // Create a sample notification
    const notification = new NotificationEntity({
      templateId: template.id,
      subscriberId: subscriber.id,
      provider: 'email',
      payload: {
        name: 'John Doe'
      },
      status: NotificationStatus.Pending,
      criticality: Criticality.Low
    });
    
    // Save all entities
    console.log('Saving entities...');
    await subscriberRepo.save(subscriber);
    await templateRepo.save(template);
    await topicRepo.save(topic);
    await notificationRepo.save(notification);
    
    // Retrieve the entities to verify
    console.log('Retrieving entities...');
    const retrievedSubscriber = await subscriberRepo.findById(subscriber.id);
    const retrievedTemplate = await templateRepo.findById(template.id);
    const retrievedTopic = await topicRepo.findById(topic.id);
    const retrievedNotification = await notificationRepo.findById(notification.id);
    
    console.log('Retrieved subscriber:', retrievedSubscriber ? 'Found' : 'Not found');
    console.log('Retrieved template:', retrievedTemplate ? 'Found' : 'Not found');
    console.log('Retrieved topic:', retrievedTopic ? 'Found' : 'Not found');
    console.log('Retrieved notification:', retrievedNotification ? 'Found' : 'Not found');
    
    console.log('Repository example completed successfully.');
    
    // Graceful shutdown
    setTimeout(() => process.exit(0), 1000);
  } catch (error) {
    console.error('Error in repository example:', error);
    process.exit(1);
  }
}

// Run the example
run();
