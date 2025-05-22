// Shakespeare notification example
import 'dotenv/config';
import { Criticality } from './models/notification'; 
import type { SubscriberEntity } from './domain/entities/SubscriberEntity'; 
import type { NotificationApplicationService } from './application/services/NotificationApplicationService';
import type { SubscriberApplicationService } from './application/services/SubscriberApplicationService';
import type { TopicApplicationService } from './application/services/TopicApplicationService';
import type { ITemplateRepository } from './domain/repositories/ITemplateRepository';
import type { SendNotificationUseCase, SendNotificationResult } from './application/useCases/SendNotificationUseCase'; 
import type { MarkNotificationAsReadUseCase } from './application/useCases/MarkNotificationAsReadUseCase'; 
import { bootstrap, type AppConfig, SERVICE_IDENTIFIERS } from './infrastructure/bootstrap'; // Corrected import for SERVICE_IDENTIFIERS

// Load provider configurations from environment variables
const appConfig = {
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
  // Define a default AppConfig
  const defaultConfig: AppConfig = {
    smsConfig: { accessToken: 'test-sms-token', apiUrl: 'https://api.sms.com/send' }, // Corrected SMSConfig
    pushConfig: { firebaseConfig: { projectId: 'test-project' } , appName: 'shakespeare-app'}, // Corrected PushConfig
    emailConfig: { transportOptions: { host: 'smtp.example.com', port: 587, secure: false } }, // Corrected EmailConfig
    mediumRetryCount: 3,
  };

  const { broker, container } = await bootstrap(defaultConfig); // Pass config to bootstrap
  console.log('Shakespeare Notification Example Started!');

  const notificationApplicationService = container.get<NotificationApplicationService>(SERVICE_IDENTIFIERS.NotificationApplicationService);
  const subscriberApplicationService = container.get<SubscriberApplicationService>(SERVICE_IDENTIFIERS.SubscriberApplicationService);
  const topicApplicationService = container.get<TopicApplicationService>(SERVICE_IDENTIFIERS.TopicApplicationService);
  const templateRepository = container.get<ITemplateRepository>(SERVICE_IDENTIFIERS.TemplateRepository);
  const sendNotificationUseCase = container.get<SendNotificationUseCase>(SERVICE_IDENTIFIERS.SendNotificationUseCase);
  const markAsReadUseCase = container.get<MarkNotificationAsReadUseCase>(SERVICE_IDENTIFIERS.MarkNotificationAsReadUseCase); 

  try {
    const { TemplateEntity } = await import('./domain/entities/TemplateEntity');
    const shakespeareTemplate = new TemplateEntity({
      id: 'shakespeare-template-fixed-id', // Using a fixed ID for predictability if needed
      name: 'Shakespeare Quote Template',
      content: '{{quote}}',
      // subject: 'A Word from Shakespeare: {{subject_line_quote}}' // Example if template had subject
    });
    await templateRepository.save(shakespeareTemplate);
    console.log('Created Shakespeare template:', shakespeareTemplate.id);

    const shakespeareTopic = await topicApplicationService.createTopic({ name: 'Shakespeare' });
    console.log('Created Shakespeare topic:', shakespeareTopic.id);

    console.log('Creating Shakespeare enthusiasts as subscribers...');
    const hamletSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'Hamlet', 
      lastName: 'Enthusiast', 
      email: 'hamlet.fan@example.com',
      phoneNumber: '+1234567890', 
      pushTokens: ['hamlet-device-token-123'] 
    });
    console.log('Created Hamlet subscriber:', hamletSubscriber.id);

    const macbethSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'Macbeth', 
      lastName: 'Fan', 
      email: 'macbeth.fan@example.com',
      phoneNumber: '+1234567891', 
      pushTokens: ['macbeth-device-token-456'] 
    });
    console.log('Created Macbeth subscriber:', macbethSubscriber.id);

    const kingLearSubscriber = await subscriberApplicationService.createSubscriber({
      firstName: 'King Lear', 
      lastName: 'Admirer', 
      email: 'kinglear.fan@example.com',
      phoneNumber: '+1234567892', 
      pushTokens: ['kinglear-device-token-789'] 
    });
    console.log('Created King Lear subscriber:', kingLearSubscriber.id);
    
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, hamletSubscriber.id); 
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, macbethSubscriber.id); 
    await topicApplicationService.addSubscriberToTopic(shakespeareTopic.id, kingLearSubscriber.id); 
    console.log('Added all subscribers to Shakespeare topic');

    // HIGH criticality - Push to Hamlet
    console.log('\\n=== Sending HIGH criticality notification to Hamlet subscriber ===');
    let highCriticalityResult = { success: false, notificationId: null as string | null, error: null as string | null };
    try {
      const result = await sendNotificationUseCase.execute({
        templateId: shakespeareTemplate.id,
        subscriberId: hamletSubscriber.id,
        provider: 'push',
        payload: { 
          token: hamletSubscriber.pushTokens[0], 
          title: 'URGENT: Special Shakespeare Event!',
        },
        templateContext: { quote: 'To be, or not to be, that is the question' },
        criticality: Criticality.High
      });
      highCriticalityResult = { success: true, notificationId: result.notification.id, error: null }; 
    } catch (e: any) {
      highCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    console.log('High criticality notification sent:', highCriticalityResult.success);
    if (!highCriticalityResult.success) {
      console.error('High criticality notification failed:', highCriticalityResult.error);
    } else if (highCriticalityResult.notificationId) {
      console.log('High criticality notification ID:', highCriticalityResult.notificationId);
      await markAsReadUseCase.execute({ notificationId: highCriticalityResult.notificationId }); 
      console.log(`Notification ${highCriticalityResult.notificationId} marked as read.`);
    }

    // MEDIUM criticality - Email to Macbeth
    console.log('\\n=== Sending MEDIUM criticality notification to Macbeth subscriber ===');
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
        templateContext: { quote: 'Double, double toil and trouble; Fire burn, and cauldron bubble' },
        criticality: Criticality.Medium
      });
      mediumCriticalityResult = { success: true, notificationId: result.notification.id, error: null }; 
    } catch (e: any) {
      mediumCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    console.log('Medium criticality notification sent:', mediumCriticalityResult.success);
    if (!mediumCriticalityResult.success) {
      console.error('Medium criticality notification failed:', mediumCriticalityResult.error);
    } else if (mediumCriticalityResult.notificationId) {
      console.log('Medium criticality notification ID:', mediumCriticalityResult.notificationId);
      await markAsReadUseCase.execute({ notificationId: mediumCriticalityResult.notificationId }); 
      console.log(`Notification ${mediumCriticalityResult.notificationId} marked as read.`);
    }
    
    // LOW criticality - SMS to King Lear
    console.log('\\n=== Sending LOW criticality notification to King Lear subscriber ===');
    let lowCriticalityResult = { success: false, notificationId: null as string | null, error: null as string | null };
    try {
      const result = await sendNotificationUseCase.execute({
        templateId: shakespeareTemplate.id,
        subscriberId: kingLearSubscriber.id,
        provider: 'sms',
        payload: { 
          to: kingLearSubscriber.phoneNumber, 
        },
        templateContext: { quote: 'Nothing will come of nothing' },
        criticality: Criticality.Low
      });
      lowCriticalityResult = { success: true, notificationId: result.notification.id, error: null }; 
    } catch (e: any) {
      lowCriticalityResult = { success: false, notificationId: null, error: e.message };
    }
    console.log('Low criticality notification sent:', lowCriticalityResult.success);
    if (!lowCriticalityResult.success) {
      console.error('Low criticality notification failed:', lowCriticalityResult.error);
    } else if (lowCriticalityResult.notificationId) {
      console.log('Low criticality notification ID:', lowCriticalityResult.notificationId);
      // await markAsReadUseCase.execute({ notificationId: lowCriticalityResult.notificationId }); 
      // console.log(`Notification ${lowCriticalityResult.notificationId} marked as read.`);
    }

    // Summary
    console.log('\\n=== Shakespeare Notification Summary ===');
    console.log(`Topic: ${shakespeareTopic.name}`);
    
    const finalHamlet = await subscriberApplicationService.getSubscriberById(hamletSubscriber.id) as SubscriberEntity | null;
    const finalMacbeth = await subscriberApplicationService.getSubscriberById(macbethSubscriber.id) as SubscriberEntity | null;
    const finalKingLear = await subscriberApplicationService.getSubscriberById(kingLearSubscriber.id) as SubscriberEntity | null;

    const hamletName = finalHamlet ? finalHamlet.fullName : 'Unknown Hamlet';
    const macbethName = finalMacbeth ? finalMacbeth.fullName : 'Unknown Macbeth';
    const kingLearName = finalKingLear ? finalKingLear.fullName : 'Unknown King Lear';
    console.log(`Subscribers: ${hamletName}, ${macbethName}, ${kingLearName}`);
    
    console.log('Notification statuses:');
    console.log(`- High priority (Push to ${hamletName}): ${highCriticalityResult.success ? 'SENT & ACKNOWLEDGED' : 'FAILED'}${highCriticalityResult.error ? ' (' + highCriticalityResult.error + ')' : ''}`);
    console.log(`- Medium priority (Email to ${macbethName}): ${mediumCriticalityResult.success ? 'SENT & ACKNOWLEDGED' : 'FAILED'}${mediumCriticalityResult.error ? ' (' + mediumCriticalityResult.error + ')' : ''}`);
    console.log(`- Low priority (SMS to ${kingLearName}): ${lowCriticalityResult.success ? 'SENT' : 'FAILED'}${lowCriticalityResult.error ? ' (' + lowCriticalityResult.error + ')' : ''}`);

  } catch (error: any) {
    console.error('\\n--- Example Script Error ---');
    console.error(error.message);
    if (error.stack) {
      console.error(error.stack);
    }
  } finally {
    if (broker) {
      await broker.stop();
    }
    console.log('\\nShakespeare Notification Example Finished!');
  }
}

main().catch(err => {
  console.error("Unhandled error in main:", err);
  process.exit(1);
});
