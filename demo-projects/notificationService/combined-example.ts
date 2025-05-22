/**
 * Combined MongoDB and Shakespeare notification example
 * 
 * This script demonstrates:
 * 1. MongoDB/In-memory repository integration
 * 2. Shakespeare-themed notification system with different channels
 * 3. Multiple notification types with varying criticality levels
 */
import 'dotenv/config';
import { bootstrap, SERVICE_IDENTIFIERS } from './infrastructure/bootstrap';
import { Criticality, NotificationStatus } from './models/notification';
import { NotificationEntity } from './domain/entities/NotificationEntity';
import { SubscriberEntity } from './domain/entities/SubscriberEntity';
import { TemplateEntity } from './domain/entities/TemplateEntity';
import { TopicEntity } from './domain/entities/TopicEntity';
import type { INotificationRepository } from './domain/repositories/INotificationRepository';
import type { ISubscriberRepository } from './domain/repositories/ISubscriberRepository';
import type { ITemplateRepository } from './domain/repositories/ITemplateRepository';
import type { ITopicRepository } from './domain/repositories/ITopicRepository';
import type { NotificationApplicationService } from './application/services/NotificationApplicationService';
import type { SubscriberApplicationService } from './application/services/SubscriberApplicationService';
import type { TopicApplicationService } from './application/services/TopicApplicationService';
import type { SendNotificationUseCase } from './application/useCases/SendNotificationUseCase';
import type { MarkNotificationAsReadUseCase } from './application/useCases/MarkNotificationAsReadUseCase';

/**
 * Shakespeare quotes by play
 */
const SHAKESPEARE_QUOTES = {
  hamlet: [
    "To be, or not to be, that is the question",
    "The lady doth protest too much, methinks",
    "Though this be madness, yet there is method in't"
  ],
  macbeth: [
    "Double, double toil and trouble; Fire burn, and cauldron bubble",
    "Fair is foul, and foul is fair",
    "Something wicked this way comes"
  ],
  kingLear: [
    "Nothing will come of nothing",
    "How sharper than a serpent's tooth it is to have a thankless child",
    "The worst is not, So long as we can say, 'This is the worst'"
  ],
  romeo: [
    "What's in a name? That which we call a rose by any other name would smell as sweet",
    "Good night, good night! Parting is such sweet sorrow",
    "These violent delights have violent ends"
  ],
  othello: [
    "O, beware, my lord, of jealousy; It is the green-eyed monster which doth mock the meat it feeds on",
    "Reputation is an idle and most false imposition; oft got without merit, and lost without deserving",
    "I am not what I am"
  ]
};

/**
 * Run the combined example
 */
async function run() {
  try {
    console.log('Starting the Combined MongoDB Shakespeare Example...');
    
    // Parse command line arguments
    const useInMemory = process.argv.includes('--in-memory');
    if (useInMemory) {
      process.env.USE_IN_MEMORY_DB = 'true';
      console.log('Using in-memory repositories (--in-memory flag detected)');
    } else {
      console.log('MongoDB URI:', process.env.MONGODB_URI || 'mongodb://localhost:27017/notification-service');
      console.log('Attempting to use MongoDB repositories...');
    }
    
    // Bootstrap application with minimal config
    const { broker, container } = await bootstrap({
      smsConfig: { 
        accessToken: process.env.SMS_TOKEN || 'mock-token' 
      },
      pushConfig: {
        firebaseConfig: {
          projectId: process.env.FIREBASE_PROJECT_ID || 'mock-project',
          clientEmail: process.env.FIREBASE_CLIENT_EMAIL || 'mock@email.com',
          privateKey: process.env.FIREBASE_PRIVATE_KEY?.replace(/\\n/g, "\n") || 'mock-key',
          appId: 'mock-app-id',
          authDomain: 'mock-domain.com',
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
          }
        }
      },
      mediumRetryCount: Number(process.env.MEDIUM_RETRY_COUNT) || 3
    });

    console.log(`Repository type: ${process.env.USE_IN_MEMORY_DB === 'true' ? 'In-Memory' : 'MongoDB'}`);
    
    // Get repository access through the container
    const notificationRepo = container.get<INotificationRepository>(SERVICE_IDENTIFIERS.NotificationRepository);
    const subscriberRepo = container.get<ISubscriberRepository>(SERVICE_IDENTIFIERS.SubscriberRepository);
    const templateRepo = container.get<ITemplateRepository>(SERVICE_IDENTIFIERS.TemplateRepository);
    const topicRepo = container.get<ITopicRepository>(SERVICE_IDENTIFIERS.TopicRepository);
    
    // Get services through the container
    const notificationApplicationService = container.get<NotificationApplicationService>(SERVICE_IDENTIFIERS.NotificationApplicationService);
    const subscriberApplicationService = container.get<SubscriberApplicationService>(SERVICE_IDENTIFIERS.SubscriberApplicationService);
    const topicApplicationService = container.get<TopicApplicationService>(SERVICE_IDENTIFIERS.TopicApplicationService);
    const sendNotificationUseCase = container.get<SendNotificationUseCase>(SERVICE_IDENTIFIERS.SendNotificationUseCase);
    const markAsReadUseCase = container.get<MarkNotificationAsReadUseCase>(SERVICE_IDENTIFIERS.MarkNotificationAsReadUseCase);

    // --------------------------- PART 1: Repository Demonstration ---------------------------
    console.log('\n=== PART 1: Testing Basic Repository Functions ===');

    // Create a template for general notifications
    const generalTemplate = new TemplateEntity({
      name: 'General Email Template',
      content: 'Hello {{name}}, {{message}}',
      parameters: ['name', 'message']
    });
    await templateRepo.save(generalTemplate);
    console.log('Created general template:', generalTemplate.id);

    // Create a topic for general notifications
    const generalTopic = new TopicEntity({
      name: 'General Notifications'
    });
    await topicRepo.save(generalTopic);
    console.log('Created general topic:', generalTopic.id);

    // Create a test subscriber
    const testSubscriber = new SubscriberEntity({
      firstName: 'Test',
      lastName: 'User',
      email: 'test@example.com',
      phoneNumber: '+1234567890',
      pushTokens: ['test-push-token']
    });
    await subscriberRepo.save(testSubscriber);
    console.log('Created test subscriber:', testSubscriber.id);

    // Create a test notification
    const testNotification = new NotificationEntity({
      templateId: generalTemplate.id,
      subscriberId: testSubscriber.id,
      provider: 'email',
      payload: {
        name: 'Test User',
        message: 'This is a test notification'
      },
      status: NotificationStatus.Pending,
      criticality: Criticality.Medium
    });
    await notificationRepo.save(testNotification);
    console.log('Created test notification:', testNotification.id);

    // Test retrieving repositories
    const retrievedSubscriber = await subscriberRepo.findById(testSubscriber.id);
    const retrievedTemplate = await templateRepo.findById(generalTemplate.id);
    const retrievedTopic = await topicRepo.findById(generalTopic.id);
    const retrievedNotification = await notificationRepo.findById(testNotification.id);
    
    console.log('\nBasic repository tests:');
    console.log('- Subscriber retrieval:', retrievedSubscriber ? 'SUCCESS' : 'FAILED');
    console.log('- Template retrieval:', retrievedTemplate ? 'SUCCESS' : 'FAILED');
    console.log('- Topic retrieval:', retrievedTopic ? 'SUCCESS' : 'FAILED');
    console.log('- Notification retrieval:', retrievedNotification ? 'SUCCESS' : 'FAILED');

    // --------------------------- PART 2: Shakespeare Notification Example ---------------------------
    console.log('\n=== PART 2: Shakespeare Notification System ===');

    // Create Shakespeare template
    const shakespeareTemplate = new TemplateEntity({
      name: 'Shakespeare Quote Template',
      content: '{{quote}}',
      parameters: ['quote']
    });
    await templateRepo.save(shakespeareTemplate);
    console.log('Created Shakespeare template:', shakespeareTemplate.id);

    // Create Shakespeare topic
    const shakespeareTopic = await topicApplicationService.createTopic({ 
      name: 'Shakespeare Quotes' 
    });
    console.log('Created Shakespeare topic:', shakespeareTopic.id);

    // Create Shakespeare enthusiasts
    console.log('\nCreating Shakespeare enthusiasts as subscribers...');
    
    const hamletSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'Hamlet', 
      lastName: 'Enthusiast', 
      email: 'hamlet.fan@example.com',
      phoneNumber: '+1234567890', 
      pushTokens: ['hamlet-device-token'] 
    });
    console.log('- Created Hamlet subscriber:', hamletSubscriber.id);

    const macbethSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'Macbeth', 
      lastName: 'Fan', 
      email: 'macbeth.fan@example.com',
      phoneNumber: '+1234567891', 
      pushTokens: ['macbeth-device-token'] 
    });
    console.log('- Created Macbeth subscriber:', macbethSubscriber.id);

    const kingLearSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'King Lear', 
      lastName: 'Admirer', 
      email: 'kinglear.fan@example.com',
      phoneNumber: '+1234567892', 
      pushTokens: ['kinglear-device-token'] 
    });
    console.log('- Created King Lear subscriber:', kingLearSubscriber.id);

    // Add subscribers to Shakespeare topic
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, hamletSubscriber.id);
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, macbethSubscriber.id);
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, kingLearSubscriber.id);
    console.log('Added all subscribers to Shakespeare topic');

    // Send notifications with different criticality levels
    console.log('\nSending Shakespeare notifications with different criticality levels...');

    // HIGH criticality - Push to Hamlet
    console.log('\n=== Sending HIGH criticality notification to Hamlet subscriber ===');
    let highCriticalityResult = { success: false, notificationId: null as string | null, error: null as string | null };
    try {
      const result = await sendNotificationUseCase.execute({
        templateId: shakespeareTemplate.id,
        subscriberId: hamletSubscriber.id,
        provider: 'push',
        payload: { 
          token: 'hamlet-device-token', 
          title: 'URGENT: Special Shakespeare Event!',
        },
        templateContext: { 
          quote: SHAKESPEARE_QUOTES.hamlet[0]
        },
        criticality: Criticality.High
      });
      highCriticalityResult = { 
        success: true, 
        notificationId: result.notification.id, 
        error: null 
      };
    } catch (e: any) {
      highCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    
    console.log('High criticality notification sent:', highCriticalityResult.success);
    if (highCriticalityResult.notificationId) {
      console.log('High criticality notification ID:', highCriticalityResult.notificationId);
      await markAsReadUseCase.execute({ notificationId: highCriticalityResult.notificationId });
      console.log(`Notification ${highCriticalityResult.notificationId} marked as read.`);
    }

    // MEDIUM criticality - Email to Macbeth
    console.log('\n=== Sending MEDIUM criticality notification to Macbeth subscriber ===');
    let mediumCriticalityResult = { success: false, notificationId: null as string | null, error: null as string | null };
    try {
      const result = await sendNotificationUseCase.execute({
        templateId: shakespeareTemplate.id,
        subscriberId: macbethSubscriber.id,
        provider: 'email',
        payload: { 
          to: macbethSubscriber.email, 
          subject: 'Shakespeare Quarterly Update',
        },
        templateContext: { 
          quote: SHAKESPEARE_QUOTES.macbeth[0]
        },
        criticality: Criticality.Medium
      });
      mediumCriticalityResult = { 
        success: true, 
        notificationId: result.notification.id, 
        error: null 
      };
    } catch (e: any) {
      mediumCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    
    console.log('Medium criticality notification sent:', mediumCriticalityResult.success);
    if (mediumCriticalityResult.notificationId) {
      console.log('Medium criticality notification ID:', mediumCriticalityResult.notificationId);
      await markAsReadUseCase.execute({ notificationId: mediumCriticalityResult.notificationId });
      console.log(`Notification ${mediumCriticalityResult.notificationId} marked as read.`);
    }
    
    // LOW criticality - SMS to King Lear
    console.log('\n=== Sending LOW criticality notification to King Lear subscriber ===');
    let lowCriticalityResult = { success: false, notificationId: null as string | null, error: null as string | null };
    try {
      const result = await sendNotificationUseCase.execute({
        templateId: shakespeareTemplate.id,
        subscriberId: kingLearSubscriber.id,
        provider: 'sms',
        payload: { 
          to: kingLearSubscriber.phoneNumber
        },
        templateContext: { 
          quote: SHAKESPEARE_QUOTES.kingLear[0]
        },
        criticality: Criticality.Low
      });
      lowCriticalityResult = { 
        success: true, 
        notificationId: result.notification.id, 
        error: null 
      };
    } catch (e: any) {
      lowCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    
    console.log('Low criticality notification sent:', lowCriticalityResult.success);
    if (lowCriticalityResult.notificationId) {
      console.log('Low criticality notification ID:', lowCriticalityResult.notificationId);
      // We intentionally don't mark this one as read
    }

    // --------------------------- PART 3: Query Repository for Results ---------------------------
    console.log('\n=== PART 3: Query Repository for Results ===');
    
    // Get all notifications for Hamlet
    const hamletNotifications = await notificationRepo.findBySubscriberId(hamletSubscriber.id);
    console.log(`\nHamlet has ${hamletNotifications.length} notification(s):`);
    hamletNotifications.forEach((notification, index) => {
      console.log(`${index + 1}. Status: ${notification.status}, Provider: ${notification.provider}`);
    });
    
    // Get all notifications for Macbeth
    const macbethNotifications = await notificationRepo.findBySubscriberId(macbethSubscriber.id);
    console.log(`\nMacbeth has ${macbethNotifications.length} notification(s):`);
    macbethNotifications.forEach((notification, index) => {
      console.log(`${index + 1}. Status: ${notification.status}, Provider: ${notification.provider}`);
    });
    
    // Get all notifications for King Lear
    const kingLearNotifications = await notificationRepo.findBySubscriberId(kingLearSubscriber.id);
    console.log(`\nKing Lear has ${kingLearNotifications.length} notification(s):`);
    kingLearNotifications.forEach((notification, index) => {
      console.log(`${index + 1}. Status: ${notification.status}, Provider: ${notification.provider}`);
    });
    
    // Get unread notifications
    const kingLearUnreadNotifications = await notificationRepo.findUnreadBySubscriberId(kingLearSubscriber.id);
    console.log(`\nKing Lear has ${kingLearUnreadNotifications.length} unread notification(s)`);
    
    // Summary
    console.log('\n=== Example Summary ===');
    console.log(`Storage type: ${process.env.USE_IN_MEMORY_DB === 'true' ? 'In-Memory' : 'MongoDB'}`);
    console.log(`Total subscribers created: 4`);
    console.log(`Total topics created: 2`);
    console.log(`Total templates created: 2`);
    console.log(`Total notifications created: 4`);
    
    // Final status of notifications
    console.log('\nNotification Statuses:');
    console.log(`- High criticality (Push to Hamlet): ${highCriticalityResult.success ? 'SENT & ACKNOWLEDGED' : 'FAILED'}${highCriticalityResult.error ? ' (' + highCriticalityResult.error + ')' : ''}`);
    console.log(`- Medium criticality (Email to Macbeth): ${mediumCriticalityResult.success ? 'SENT & ACKNOWLEDGED' : 'FAILED'}${mediumCriticalityResult.error ? ' (' + mediumCriticalityResult.error + ')' : ''}`);
    console.log(`- Low criticality (SMS to King Lear): ${lowCriticalityResult.success ? 'SENT (UNACKNOWLEDGED)' : 'FAILED'}${lowCriticalityResult.error ? ' (' + lowCriticalityResult.error + ')' : ''}`);

    // Graceful shutdown
    await broker.stop();
    console.log('\nCombined Example Completed Successfully!');
    
    // Allow time for any async operations to complete before exiting
    setTimeout(() => process.exit(0), 1000);

  } catch (error: any) {
    console.error('\n❌ ERROR in combined example:', error.message);
    if (error.stack) {
      console.error(error.stack);
    }
    process.exit(1);
  }
}

// Run the combined example
run();
