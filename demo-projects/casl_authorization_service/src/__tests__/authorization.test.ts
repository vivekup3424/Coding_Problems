import { ServiceBroker } from 'moleculer';
import LocalAuthorizationService from '../services/local-authorization.service';
import CloudAuthorizationService from '../services/cloud-authorization.service';

describe('Authorization Services', () => {
  let broker: ServiceBroker;

  beforeAll(async () => {
    broker = new ServiceBroker({
      logger: false,
      transporter: null
    });
    
    broker.createService(LocalAuthorizationService);
    broker.createService(CloudAuthorizationService);
    
    await broker.start();
  });

  afterAll(async () => {
    await broker.stop();
  });

  describe('Local Authorization Service', () => {
    test('should check user permissions correctly', async () => {
      const result = await broker.call('1.0.0.local-authorization.can', {
        userId: 'user_001',
        action: 'read',
        subject: 'device'
      }) as { allowed: boolean; reason?: string };

      expect(result).toHaveProperty('allowed');
      expect(typeof result.allowed).toBe('boolean');
    });

    test('should get user permissions', async () => {
      const permissions = await broker.call('1.0.0.local-authorization.getUserPermissions', {
        userId: 'user_001'
      }) as any[];

      expect(Array.isArray(permissions)).toBe(true);
    });
  });

  describe('Cloud Authorization Service', () => {
    test('should check cloud permissions', async () => {
      const result = await broker.call('1.0.0.cloud-authorization.can', {
        userId: 'user_002',
        action: 'configure',
        subject: 'home'
      }) as { allowed: boolean; reason?: string };

      expect(result).toHaveProperty('allowed');
    });

    test('should get user roles', async () => {
      const roles = await broker.call('1.0.0.cloud-authorization.getUserRoles', {
        userId: 'user_001'
      }) as string[];

      expect(Array.isArray(roles)).toBe(true);
    });
  });
});
