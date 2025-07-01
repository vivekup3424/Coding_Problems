import { ServiceBroker } from 'moleculer';
import AuthenticationService from './services/authentication.service';
import LocalAuthorizationService from './services/local-authorization.service';
import CloudAuthorizationService from './services/cloud-authorization.service';

/**
 * Main entry point for the CASL Authorization Service
 * Sets up MoleculerJS broker and registers all services
 */
const broker = new ServiceBroker({
  nodeID: 'casl-auth-node',
  logLevel: 'info',
  transporter: process.env.TRANSPORTER || 'TCP',
  cacher: process.env.CACHER || 'Memory',
  serializer: 'JSON',
  
  // Request timeout
  requestTimeout: 10 * 1000,
  
  // Retry policy
  retryPolicy: {
    enabled: false,
    retries: 5,
    delay: 100,
    maxDelay: 1000,
    factor: 2,
    check: (err: any) => err && !!err.retryable
  },

  // Fault tolerance
  circuitBreaker: {
    enabled: false,
    threshold: 0.5,
    minRequestCount: 20,
    windowTime: 60,
    halfOpenTime: 10 * 1000,
    check: (err: any) => err && err.code >= 500
  },

  // Registry settings
  registry: {
    strategy: 'RoundRobin',
    preferLocal: true
  },

  // Metrics
  metrics: {
    enabled: true,
    reporter: {
      type: 'Console',
      options: {
        logger: null,
        colors: true,
        width: 100,
        gaugeWidth: 40
      }
    }
  },

  // Tracing
  tracing: {
    enabled: true,
    exporter: {
      type: 'Console',
      options: {
        logger: null,
        colors: true,
        width: 100,
        gaugeWidth: 40
      }
    }
  }
});

// Register services
broker.createService(AuthenticationService);
broker.createService(LocalAuthorizationService);
broker.createService(CloudAuthorizationService);

// Start the broker
broker.start()
  .then(() => {
    broker.logger.info('🚀 CASL Authorization Service started successfully');
    broker.logger.info('📋 Available services:');
    broker.logger.info('  - authentication: User login and JWT management');
    broker.logger.info('  - local-authorization: Local permission checking');
    broker.logger.info('  - cloud-authorization: Cloud permission checking');
  })
  .catch((err) => {
    broker.logger.error('❌ Failed to start CASL Authorization Service:', err);
    process.exit(1);
  });

// Graceful shutdown
process.on('SIGINT', () => {
  broker.logger.info('📴 Shutting down CASL Authorization Service...');
  broker.stop()
    .then(() => {
      broker.logger.info('✅ Service shutdown complete');
      process.exit(0);
    })
    .catch((err) => {
      broker.logger.error('❌ Error during shutdown:', err);
      process.exit(1);
    });
});

export default broker;
