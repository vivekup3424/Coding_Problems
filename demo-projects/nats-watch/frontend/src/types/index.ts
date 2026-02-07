// Server types
export type AuthType = 'none' | 'token' | 'userpass';

export interface Server {
  id: number;
  name: string;
  url: string;
  auth_type: AuthType;
  auth_token?: string;
  auth_username?: string;
  auth_password?: string;
  is_active: boolean;
  created_at: string;
  updated_at: string;
}

export interface ServerCreateRequest {
  name: string;
  url: string;
  auth_type: AuthType;
  auth_token?: string;
  auth_username?: string;
  auth_password?: string;
}

// NATS data types
export interface VarzData {
  server_id: string;
  server_name: string;
  version: string;
  uptime: string;
  mem: number;
  cpu: number;
  connections: number;
  total_connections: number;
  in_msgs: number;
  out_msgs: number;
  in_bytes: number;
  out_bytes: number;
  slow_consumers: number;
}

export interface Connection {
  cid: number;
  name: string;
  lang: string;
  version: string;
  ip: string;
  port: number;
  start: string;
  uptime: string;
  in_msgs: number;
  out_msgs: number;
  subscriptions?: string[];
  subscriptions_list?: string[];
}

export interface ConnzData {
  num_connections: number;
  connections: Connection[];
}

export interface SubzData {
  num_subscriptions: number;
  num_cache: number;
  subscriptions_list?: string[];
}

// Label types
export interface LabelCategory {
  id: number;
  server_id: number;
  name: string;
  rules?: LabelRule[];
  created_at: string;
  updated_at: string;
}

export interface LabelRule {
  id: number;
  category_id: number;
  label_value: string;
  pattern: string;
  priority: number;
  created_at: string;
  updated_at: string;
}

// WebSocket types
export type WSMessageType = 'varz' | 'connz' | 'subz' | 'alert';

export interface WSMessage<T = unknown> {
  type: WSMessageType;
  timestamp: string;
  data: T;
}

// UI state types
export interface ClientWithLabels extends Connection {
  labels: Record<string, string>;
}

export interface SubjectNode {
  name: string;
  fullPath: string;
  subscriberCount: number;
  children: Record<string, SubjectNode>;
}
