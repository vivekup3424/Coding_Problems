import { Service, ServiceBroker, Context } from 'moleculer';
import { readFileSync } from 'fs';
import { join } from 'path';
import { config } from '../config';
import { Permission, Room, Device, User } from "../types"
import { createMongoAbility, subject } from '@casl/ability';
export default class LocalAuthorizationService extends Service {

  public constructor(broker: ServiceBroker) {
    super(broker);
    this.parseServiceSchema({
      name: config.services.localAuthorization.name,
      version: config.services.localAuthorization.version,

      actions: {
        can: {
          handler: this.can
        },
        getUserPermissions: {
          handler: this.getUserPermissions
        },
        getUserAccessibleRooms: {
          params: {
            userId: 'string'
          },
          handler: this.getUserAccessibleRooms
        },
        getUserAccessibleDevices: {
          params: {
            userId: 'string'
          },
          handler: this.getUserAccessibleDevices
        }
      },
    });
  }
  private getAllUserPermissions(userId: string): Permission[] {
    const permissionsPath = join(process.cwd(), config.dataFiles.localPermissions);
    const permissionsData = readFileSync(permissionsPath, 'utf8');
    const permissions = JSON.parse(permissionsData);
    const userRolesPath = join(process.cwd(), './data/user-roles.json');
    const userRolesData = readFileSync(userRolesPath, 'utf8');
    const userRoles = JSON.parse(userRolesData);
    if (!permissions || !userRoles) {
      return [];
    }
    
    const allPermissions: Permission[] = permissions[userId];
    const roles = userRoles[userId] || [];
    roles.forEach((role: string) => {
      const rolePermissions = permissions[role] || [];
      allPermissions.push(...rolePermissions);
    });

    return allPermissions;
  }

  private getUserData(userId: string): User | null {
    try {
      const authDataPath = join(process.cwd(), './data/authentication-data.json');
      const authData = readFileSync(authDataPath, 'utf8');
      const parsedAuthData = JSON.parse(authData);
      return parsedAuthData.users.find((user: User) => user.id === userId) || null;
    } catch (error) {
      this.logger.error('Failed to load user data:', error);
      return null;
    }
  }

  private getAllRooms(): Room[] {
    try {
      const roomsDataPath = join(process.cwd(), './data/rooms-data.json');
      const roomsData = readFileSync(roomsDataPath, 'utf8');
      const parsedRoomsData = JSON.parse(roomsData);
      return parsedRoomsData.rooms || [];
    } catch (error) {
      this.logger.error('Failed to load rooms data:', error);
      return [];
    }
  }

  private getAllDevices(): Device[] {
    try {
      const devicesDataPath = join(process.cwd(), './data/devices-data.json');
      const devicesData = readFileSync(devicesDataPath, 'utf8');
      const parsedDevicesData = JSON.parse(devicesData);
      return parsedDevicesData.devices || [];
    } catch (error) {
      this.logger.error('Failed to load devices data:', error);
      return [];
    }
  }

  async can(ctx: Context<{
    userId: string;
    action: string;
    subject: string;
  }>): Promise<{ allowed: boolean; reason?: string }> {
    const { userId, action, subject } = ctx.params;
    
    const userPermissions = this.getAllUserPermissions(userId);
    if (userPermissions.length === 0) {
      return { allowed: false, reason: 'User has no permissions' };
    }
    
    const userAbility = createMongoAbility(userPermissions as any);
    const hasPermission = userAbility.can(action, subject);
    return { allowed: hasPermission };
  }

  async getUserPermissions(ctx: Context<{ userId: string }>): Promise<Permission[]> {
    const { userId } = ctx.params;
    return this.getAllUserPermissions(userId);
  }

  async getUserAccessibleRooms(ctx: Context<{ userId: string }>): Promise<Room[]> {
    const { userId } = ctx.params;
    
    const user = this.getUserData(userId);
    if (!user) return [];

    const userPermissions = this.getAllUserPermissions(userId);
    if (userPermissions.length === 0) return [];

    const userAbility = createMongoAbility(userPermissions as any);
    const allRooms = this.getAllRooms();
    
    return allRooms.filter(room => {
      const roomWithContext = { ...room, user };
      return userAbility.can('read', subject('room', roomWithContext));
    });
  }

  async getUserAccessibleDevices(ctx: Context<{ userId: string }>): Promise<Device[]> {
    const { userId } = ctx.params;
    
    const user = this.getUserData(userId);
    if (!user) return [];

    const userPermissions = this.getAllUserPermissions(userId);
    if (userPermissions.length === 0) return [];

    const userAbility = createMongoAbility(userPermissions as any);
    const allDevices = this.getAllDevices();
    
    return allDevices.filter(device => {
      const deviceWithContext = { ...device, user };
      return userAbility.can('read', subject('device', deviceWithContext));
    });
  }
}