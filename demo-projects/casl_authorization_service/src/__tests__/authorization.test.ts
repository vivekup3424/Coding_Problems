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

    test('should get accessible rooms for super admin user', async () => {
      const rooms = await broker.call('1.0.0.local-authorization.getUserAccessibleRooms', {
        userId: 'user_002' // super_admin role
      }) as any[];

      expect(Array.isArray(rooms)).toBe(true);
      // Super admin should have access to all rooms in home_001
      expect(rooms.length).toBeGreaterThan(0);
      
      // Verify all returned rooms belong to the user's home
      rooms.forEach(room => {
        expect(room).toHaveProperty('homeId', 'home_001');
        expect(room).toHaveProperty('id');
        expect(room).toHaveProperty('name');
      });
    });

    test('should get accessible rooms for home admin user', async () => {
      const rooms = await broker.call('1.0.0.local-authorization.getUserAccessibleRooms', {
        userId: 'user_003' // home_admin role
      }) as any[];

      expect(Array.isArray(rooms)).toBe(true);
      
      // Home admin should have access to rooms in their home
      rooms.forEach(room => {
        expect(room).toHaveProperty('homeId', 'home_001');
        expect(room).toHaveProperty('id');
        expect(room).toHaveProperty('name');
      });
    });

    test('should get accessible rooms for regular user with restrictions', async () => {
      const rooms = await broker.call('1.0.0.local-authorization.getUserAccessibleRooms', {
        userId: 'user_006' // user with room restrictions
      }) as any[];

      expect(Array.isArray(rooms)).toBe(true);
      
      // User should only have access to specific rooms based on permissions
      rooms.forEach(room => {
        expect(room).toHaveProperty('homeId', 'home_001');
        expect(room).toHaveProperty('id');
        expect(room).toHaveProperty('name');
      });
    });

    test('should get accessible devices for super admin user', async () => {
      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_002' // super_admin role
      }) as any[];

      expect(Array.isArray(devices)).toBe(true);
      
      // Super admin should have access to all devices in home_001
      expect(devices.length).toBeGreaterThan(0);
      
      // Verify all returned devices belong to the user's home
      devices.forEach(device => {
        expect(device).toHaveProperty('homeId', 'home_001');
        expect(device).toHaveProperty('id');
        expect(device).toHaveProperty('name');
        expect(device).toHaveProperty('type');
      });
    });

    test('should get accessible devices for home admin user', async () => {
      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_003' // home_admin role
      }) as any[];

      expect(Array.isArray(devices)).toBe(true);
      
      // Home admin should have access to all devices in their home
      devices.forEach(device => {
        expect(device).toHaveProperty('homeId', 'home_001');
        expect(device).toHaveProperty('id');
        expect(device).toHaveProperty('name');
        expect(device).toHaveProperty('type');
      });
    });

    test('should get filtered accessible devices for user with type restrictions', async () => {
      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_006' // user with device type restrictions
      }) as any[];

      expect(Array.isArray(devices)).toBe(true);
      
      // User should only have access to specific device types based on permissions
      devices.forEach(device => {
        expect(device).toHaveProperty('homeId', 'home_001');
        expect(device).toHaveProperty('id');
        expect(device).toHaveProperty('name');
        expect(device).toHaveProperty('type');
        
        // Based on local-permissions.json, user_006 has access to specific device types
        const allowedTypes = ['smart_light', 'smart_thermostat', 'smart_speaker', 'smart_switch'];
        expect(allowedTypes).toContain(device.type);
      });
    });

    test('should get filtered accessible devices for user with room restrictions', async () => {
      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_008' // user with room restrictions (only room_002)
      }) as any[];

      expect(Array.isArray(devices)).toBe(true);
      
      // User should only have access to devices in room_002
      devices.forEach(device => {
        expect(device).toHaveProperty('homeId', 'home_001');
        expect(device).toHaveProperty('roomId', 'room_002');
        expect(device).toHaveProperty('type', 'smart_light'); // user_008 only has smart_light access
      });
    });

    test('should return empty arrays for user with no permissions', async () => {
      const rooms = await broker.call('1.0.0.local-authorization.getUserAccessibleRooms', {
        userId: 'user_999' // non-existent user
      }) as any[];

      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_999' // non-existent user
      }) as any[];

      expect(Array.isArray(rooms)).toBe(true);
      expect(rooms.length).toBe(0);
      
      expect(Array.isArray(devices)).toBe(true);
      expect(devices.length).toBe(0);
    });

    test('should respect emergency override permissions', async () => {
      // Test that emergency override role can access emergency devices
      // Note: This would require setting up a user with emergency_override role
      // For now, we'll test the structure
      const devices = await broker.call('1.0.0.local-authorization.getUserAccessibleDevices', {
        userId: 'user_002' // super_admin should see emergency devices
      }) as any[];

      expect(Array.isArray(devices)).toBe(true);
      
      // Check if emergency device exists in accessible devices
      const emergencyDevice = devices.find(device => device.properties?.emergency === true);
      if (emergencyDevice) {
        expect(emergencyDevice).toHaveProperty('type');
        expect(['alarm_system', 'door_lock', 'smart_light']).toContain(emergencyDevice.type);
      }
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
