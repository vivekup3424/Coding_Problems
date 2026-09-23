export interface Permission {
  action: string | string[]
  subject?: string | string[]
  /** an array of fields to which user has (or not) access */
  fields?: string[]
  /** an object of conditions which restricts the rule scope */
  conditions?: any
  /** indicates whether rule allows or forbids something */
  inverted?: boolean
  /** message which explains why rule is forbidden */
  reason?: string
}
export interface User {
  id: string;
  username: string;
  email: string;
  passwordHash: string;
  roles: string[]
  createdAt: string;
  lastLogin: string;
  profile: {
    firstName: string;
    lastName: string;
    homeId: string;
  };
}

export interface Room {
  id: string;
  name: string;
  homeId: string;
  floor?: number;
  type: 'living_room' | 'bedroom' | 'kitchen' | 'bathroom' | 'entrance' | 'garage' | 'office' | 'guest_room' | 'dining_room' | 'other';
  description?: string;
  devices: string[]; // Array of device IDs
}

export interface Device {
  id: string;
  name: string;
  type: 'smart_light' | 'smart_thermostat' | 'security_camera' | 'door_lock' | 'smart_speaker' | 'smart_switch' | 'motion_sensor' | 'alarm_system' | 'other';
  roomId: string;
  homeId: string;
  capabilities: string[];
  status: 'online' | 'offline' | 'error';
  manufacturer?: string;
  model?: string;
  firmwareVersion?: string;
  lastUpdated: string;
  settings?: {
    [key: string]: any;
  };
}

export interface Home {
  id: string;
  name: string;
  address?: string;
  ownerId: string; // Reference to User who owns this home
  timezone: string;
  createdAt: string;
  status: 'active' | 'inactive';
  settings?: {
    emergencyContacts?: string[];
    securitySettings?: any;
  };
}