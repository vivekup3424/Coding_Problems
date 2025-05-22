interface DatabaseConfig {
  uri: string;
  useInMemory: boolean;
}

interface EmailConfig {
  host: string;
  port: number;
  secure: boolean;
  auth: {
    user: string;
    pass: string;
  }
}

interface SMSConfig {
  accountSid: string;
  authToken: string;
  phoneNumber: string;
}

interface PushConfig {
  projectId: string;
  clientEmail: string;
  privateKey: string;
}

interface AppConfig {
  database: DatabaseConfig;
  email: EmailConfig;
  sms: SMSConfig;
  push: PushConfig;
  enableMoleculer: boolean;
}

/**
 * Load configuration from environment variables
 */
export function loadConfig(): AppConfig {
  return {
    database: {
      uri: process.env.MONGODB_URI || 'mongodb://172.24.128.1:27018/notification-service',
      useInMemory: process.env.USE_IN_MEMORY_DB === 'true'
    },
    email: {
      host: process.env.EMAIL_HOST || 'smtp.example.com',
      port: parseInt(process.env.EMAIL_PORT || '587', 10),
      secure: process.env.EMAIL_SECURE === 'true',
      auth: {
        user: process.env.EMAIL_USER || '',
        pass: process.env.EMAIL_PASS || ''
      }
    },
    sms: {
      accountSid: process.env.SMS_ACCOUNT_SID || '',
      authToken: process.env.SMS_AUTH_TOKEN || '',
      phoneNumber: process.env.SMS_PHONE_NUMBER || ''
    },
    push: {
      projectId: process.env.FIREBASE_PROJECT_ID || '',
      clientEmail: process.env.FIREBASE_CLIENT_EMAIL || '',
      privateKey: process.env.FIREBASE_PRIVATE_KEY?.replace(/\\n/g, '\n') || ''
    },
    enableMoleculer: process.env.ENABLE_MOLECULER === 'true'
  };
}

export type { AppConfig, DatabaseConfig, EmailConfig, SMSConfig, PushConfig };
