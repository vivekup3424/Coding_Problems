// Shakespeare notification example
import 'dotenv/config';
import { bootstrap } from './infrastructure/bootstrap';
import type { AppConfig } from './infrastructure/bootstrap';
import { Criticality } from './models/notification';

// Load provider configurations from environment variables
const appConfig: AppConfig = {
  smsConfig: { 
    accessToken: process.env.SMS_TOKEN || 'mock-token' 
  },
  pushConfig: {
    firebaseConfig: {
      projectId: process.env.FIREBASE_PROJECT_ID || 'mock-project',
      clientEmail: process.env.FIREBASE_CLIENT_EMAIL || 'mock@email.com',
      privateKey: process.env.FIREBASE_PRIVATE_KEY?.replace(/\\n/g, "\n") || 'mock-key',
    }
  },
  emailConfig: {
    transportOptions: {
      host: process.env.SMTP_HOST || 'smtp.example.com',
      port: Number(process.env.SMTP_PORT) || 587,
      secure: false,
      auth: { 
        user: process.env.SMTP_USER || 'user@example.com', 
        pass: process.env.SMTP_PASS || 'password' 
      },
    }
  },
  mediumRetryCount: Number(process.env.MEDIUM_RETRY_COUNT) || 3
};

// Initialize the application
async function main() {
  const { broker, container } = await bootstrap(appConfig);
  
  console.log('Shakespeare Notification Example Started!');
  
  try {
    // Get repositories and services
    const topicApplicationService = container.get('topicApplicationService') as any;
    const subscriberApplicationService = container.get('subscriberApplicationService') as any;
    const sendNotificationUseCase = container.get('sendNotificationUseCase') as any;
    const markAsReadUseCase = container.get('markAsReadUseCase') as any;
    
    // Create Shakespeare topic
    const shakespeareTopic = await topicApplicationService.createTopic({
      name: 'Shakespeare',
      description: 'Notifications about Shakespeare plays and events'
    });
    console.log('Created Shakespeare topic:', shakespeareTopic.id);
    
    // Create subscribers
    console.log('\nCreating Shakespeare enthusiasts as subscribers...');
    
    // Subscriber 1 - Hamlet fan
    const hamletSubscriber = await subscriberApplicationService.createSubscriber({
      name: 'Hamlet Enthusiast',
      email: 'hamlet.fan@example.com',
      phone: '+1234567890',
      deviceToken: 'hamlet-device-token-123'
    });
    console.log('Created Hamlet subscriber:', hamletSubscriber.id);
    
    // Subscriber 2 - Macbeth fan
    const macbethSubscriber = await subscriberApplicationService.createSubscriber({
      name: 'Macbeth Enthusiast',
      email: 'macbeth.fan@example.com',
      phone: '+1987654321',
      deviceToken: 'macbeth-device-token-456'
    });
    console.log('Created Macbeth subscriber:', macbethSubscriber.id);
    
    // Subscriber 3 - King Lear fan
    const kingLearSubscriber = await subscriberApplicationService.createSubscriber({
      name: 'King Lear Enthusiast',
      email: 'kinglear.fan@example.com',
      phone: '+1555555555',
      deviceToken: 'kinglear-device-token-789'
    });
    console.log('Created King Lear subscriber:', kingLearSubscriber.id);
    
    // Add subscribers to Shakespeare topic
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, hamletSubscriber.id);
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, macbethSubscriber.id);
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, kingLearSubscriber.id);
    console.log('Added all subscribers to Shakespeare topic');
    
    // Send HIGH criticality notification to a specific subscriber
    console.log('\n=== Sending HIGH criticality notification to Hamlet subscriber ===');
    const highCriticalityResult = await sendNotificationUseCase.execute({
      subscriberId: hamletSubscriber.id,
      provider: 'push',
      payload: { 
        token: hamletSubscriber.deviceToken, // Required token for push notifications
        title: 'URGENT: Special Shakespeare Event!',
        body: 'Hamlet performance tonight!'
      },
      criticality: Criticality.High
    });
    
    console.log('High criticality notification sent:', highCriticalityResult.success);
    if (highCriticalityResult.success && highCriticalityResult.notification) {
      console.log('Notification details:', highCriticalityResult.notification.toJSON());
      
      // Simulate subscriber acknowledgment for high criticality notification
      console.log('\n=== Subscriber acknowledging HIGH criticality notification ===');
      await markAsReadUseCase.execute({
        notificationId: highCriticalityResult.notification.id,
        subscriberId: hamletSubscriber.id
      });
      console.log(`${hamletSubscriber.name} has acknowledged the notification`);
    } else {
      console.log('High criticality notification failed:', highCriticalityResult.error);
    }
    
    // Send MEDIUM criticality notification to a specific subscriber
    console.log('\n=== Sending MEDIUM criticality notification to Macbeth subscriber ===');
    const mediumCriticalityResult = await sendNotificationUseCase.execute({
      subscriberId: macbethSubscriber.id,
      provider: 'email',
      payload: { 
        to: macbethSubscriber.email,
        subject: 'Shakespeare Quarterly Update',
        body: 'Macbeth performance announcement'
      },
      criticality: Criticality.Medium
    });
    
    console.log('Medium criticality notification sent:', mediumCriticalityResult.success);
    if (mediumCriticalityResult.success && mediumCriticalityResult.notification) {
      console.log('Notification details:', mediumCriticalityResult.notification.toJSON());
    } else {
      console.log('Medium criticality notification failed:', mediumCriticalityResult.error);
    }
    
    // Send LOW criticality notification to a specific subscriber
    console.log('\n=== Sending LOW criticality notification to King Lear subscriber ===');
    const lowCriticalityResult = await sendNotificationUseCase.execute({
      subscriberId: kingLearSubscriber.id,
      provider: 'sms',
      payload: { 
        to: kingLearSubscriber.phone,
        message: 'King Lear quote of the day!'  // SMS requires "message" not "body"
      },
      criticality: Criticality.Low
    });
    
    console.log('Low criticality notification sent:', lowCriticalityResult.success);
    if (lowCriticalityResult.success && lowCriticalityResult.notification) {
      console.log('Notification details:', lowCriticalityResult.notification.toJSON());
    } else {
      console.log('Low criticality notification failed:', lowCriticalityResult.error);
    }
    
    // Display summary of notifications
    console.log('\n=== Shakespeare Notification Summary ===');
    console.log(`Topic: ${shakespeareTopic.name}`);
    console.log(`Subscribers: ${hamletSubscriber.name}, ${macbethSubscriber.name}, ${kingLearSubscriber.name}`);
    console.log('Notification statuses:');
    console.log(`- High priority: ${highCriticalityResult.success ? 'SENT' : 'FAILED'}`);
    console.log(`- Medium priority: ${mediumCriticalityResult.success ? 'SENT' : 'FAILED'}`);
    console.log(`- Low priority: ${lowCriticalityResult.success ? 'SENT' : 'FAILED'}`);
    
  } catch (error) {
    console.error('Error in Shakespeare notification example:', error);
  } finally {
    // Shutdown the broker
    await broker.stop();
  }
}

main().catch(err => {
  console.error('Failed to run Shakespeare example:', err);
  process.exit(1);
});
