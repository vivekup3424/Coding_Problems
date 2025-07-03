import { ServiceBroker } from 'moleculer';
import AuthenticationService from './services/authentication.service';
import LocalAuthorizationService from './services/local-authorization.service';
import CloudAuthorizationService from './services/cloud-authorization.service';

const broker = new ServiceBroker({
  nodeID: 'casl-auth-node',
  logLevel: 'info',
});

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
    broker.repl();
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
