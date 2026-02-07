import type { Server, ServerCreateRequest, LabelCategory, LabelRule } from '../types';

const API_BASE = '/api';

// Server API
export async function fetchServers(): Promise<Server[]> {
  const res = await fetch(`${API_BASE}/servers`);
  const data = await res.json();
  return data.servers || [];
}

export async function createServer(server: ServerCreateRequest): Promise<Server> {
  const res = await fetch(`${API_BASE}/servers`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(server),
  });
  return res.json();
}

export async function updateServer(id: number, server: Partial<ServerCreateRequest>): Promise<void> {
  await fetch(`${API_BASE}/servers/${id}`, {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(server),
  });
}

export async function deleteServer(id: number): Promise<void> {
  await fetch(`${API_BASE}/servers/${id}`, { method: 'DELETE' });
}

export async function activateServer(id: number): Promise<void> {
  await fetch(`${API_BASE}/servers/${id}/activate`, { method: 'PUT' });
}

export async function testServer(id: number): Promise<{ success: boolean; server_name?: string; version?: string; error?: string }> {
  const res = await fetch(`${API_BASE}/servers/${id}/test`, { method: 'POST' });
  return res.json();
}

// NATS data API
export async function fetchVarz() {
  const res = await fetch(`${API_BASE}/proxy/varz`);
  if (!res.ok) throw new Error('Failed to fetch varz');
  return res.json();
}

export async function fetchConnz() {
  const res = await fetch(`${API_BASE}/proxy/connz`);
  if (!res.ok) throw new Error('Failed to fetch connz');
  return res.json();
}

export async function fetchSubz() {
  const res = await fetch(`${API_BASE}/proxy/subz`);
  if (!res.ok) throw new Error('Failed to fetch subz');
  return res.json();
}

// Labels API
export async function fetchLabels(serverId: number): Promise<LabelCategory[]> {
  const res = await fetch(`${API_BASE}/labels?server_id=${serverId}`);
  const data = await res.json();
  return data.categories || [];
}

export async function createLabelCategory(serverId: number, name: string): Promise<LabelCategory> {
  const res = await fetch(`${API_BASE}/labels?server_id=${serverId}`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ name }),
  });
  return res.json();
}

export async function createLabelRule(categoryId: number, rule: Omit<LabelRule, 'id' | 'category_id' | 'created_at' | 'updated_at'>): Promise<LabelRule> {
  const res = await fetch(`${API_BASE}/rules/${categoryId}`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(rule),
  });
  return res.json();
}

export async function deleteLabel(id: number): Promise<void> {
  await fetch(`${API_BASE}/labels/${id}`, { method: 'DELETE' });
}

export async function deleteRule(id: number): Promise<void> {
  await fetch(`${API_BASE}/rules/${id}`, { method: 'DELETE' });
}
