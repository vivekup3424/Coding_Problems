# NATSWatch - Interface Specification

Technical specification for interfaces, data models, and API contracts.

---

## 1. System Architecture

```
+-------------------+        +--------------------+        +-----------------------+
|   React + Vite    |<--WSS->|   Go Backend       |<--HTTP>|  NATS Server(s)       |
|   TypeScript      |        |                    |        |  /varz /connz /subz   |
|   Tailwind CSS    |        |  - HTTP API        |        |  /jsz                 |
+-------------------+        |  - WebSocket       |        +-----------------------+
                             |  - Poller          |
                             |  - Alert Engine    |        +-----------------------+
                             |                    |<------>|  SQLite               |
                             +--------------------+        |  configs/alerts/      |
                                                           |  snapshots            |
                                                           +-----------------------+
```

### Tech Stack

| Layer | Technology | Rationale |
|-------|------------|-----------|
| Frontend | React 18 + Vite + TypeScript | Fast dev cycle, type safety |
| Styling | Tailwind CSS | Rapid UI development |
| Charts | Recharts | Lightweight, React-native |
| Backend | Go 1.21+ | Small binary, NATS ecosystem affinity |
| Realtime | gorilla/websocket | Battle-tested WebSocket library |
| Database | SQLite | Zero-config embedded storage |
| Deployment | Docker Compose | Single command local setup |

---

## 2. External Interface: NATS Monitoring API

Endpoints consumed from NATS servers.

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/varz` | GET | Server statistics (CPU, memory, connections, messages) |
| `/connz?subs=detail` | GET | Active client connections with subscription details |
| `/subz?subs=1` | GET | Subscription information by subject |
| `/jsz` | GET | JetStream streams and consumers |
| `/routez` | GET | Cluster route information |
| `/leafz` | GET | Leaf node connections |

### Authentication Headers

```
# Token-based
Authorization: token <auth_token>

# Basic Auth (user/password)
Authorization: Basic <base64(username:password)>
```

### Sample `/varz` Response

```json
{
  "server_id": "NCXCJ...",
  "server_name": "nats-prod-1",
  "version": "2.10.4",
  "uptime": "14d3h25m",
  "mem": 536870912,
  "cpu": 12.5,
  "connections": 1234,
  "total_connections": 98765,
  "in_msgs": 5000000,
  "out_msgs": 4800000,
  "in_bytes": 1073741824,
  "out_bytes": 1048576000,
  "slow_consumers": 0
}
```

### Sample `/connz` Response

```json
{
  "num_connections": 1234,
  "connections": [
    {
      "cid": 1,
      "name": "order-service",
      "lang": "go",
      "version": "1.31.0",
      "ip": "192.168.1.10",
      "port": 45678,
      "start": "2024-01-15T10:30:00Z",
      "uptime": "5d2h",
      "in_msgs": 50000,
      "out_msgs": 48000,
      "subscriptions": ["orders.>", "events.orders.*"]
    }
  ]
}
```

### Sample `/subz` Response

```json
{
  "num_subscriptions": 5678,
  "num_cache": 100,
  "subscriptions_list": [
    "orders.created",
    "orders.updated",
    "orders.cancelled",
    "users.>",
    "inventory.*"
  ]
}
```

---

## 3. Data Model (SQLite)

### servers

| Column | Type | Constraints | Description |
|--------|------|-------------|-------------|
| id | INTEGER | PK, AUTOINCREMENT | Unique identifier |
| name | TEXT | NOT NULL | Display name |
| url | TEXT | NOT NULL | Monitoring endpoint URL |
| auth_type | TEXT | NOT NULL, DEFAULT 'none' | 'none', 'token', 'userpass' |
| auth_token | TEXT | NULLABLE | Encrypted token |
| auth_username | TEXT | NULLABLE | Username for basic auth |
| auth_password | TEXT | NULLABLE | Encrypted password |
| is_active | INTEGER | DEFAULT 0 | 1 = currently selected |
| created_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |
| updated_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |

### label_categories

| Column | Type | Constraints | Description |
|--------|------|-------------|-------------|
| id | INTEGER | PK, AUTOINCREMENT | |
| server_id | INTEGER | FK(servers.id) ON DELETE CASCADE | |
| name | TEXT | NOT NULL | e.g., "Environment", "Team" |
| created_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |
| updated_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |

### label_rules

| Column | Type | Constraints | Description |
|--------|------|-------------|-------------|
| id | INTEGER | PK, AUTOINCREMENT | |
| category_id | INTEGER | FK(label_categories.id) ON DELETE CASCADE | |
| label_value | TEXT | NOT NULL | e.g., "Production" |
| pattern | TEXT | NOT NULL | Regex pattern for client name |
| priority | INTEGER | DEFAULT 0 | Higher = evaluated first |
| created_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |
| updated_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |

### client_labels

| Column | Type | Constraints | Description |
|--------|------|-------------|-------------|
| id | INTEGER | PK, AUTOINCREMENT | |
| server_id | INTEGER | FK(servers.id) ON DELETE CASCADE | |
| client_id | TEXT | NOT NULL | CID from NATS /connz |
| category_id | INTEGER | FK(label_categories.id) ON DELETE CASCADE | |
| label_value | TEXT | NOT NULL | |
| created_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |
| updated_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |

### alert_rules (P2)

| Column | Type | Constraints | Description |
|--------|------|-------------|-------------|
| id | INTEGER | PK, AUTOINCREMENT | |
| server_id | INTEGER | FK(servers.id) ON DELETE CASCADE | |
| metric | TEXT | NOT NULL | e.g., "slow_consumers" |
| operator | TEXT | NOT NULL | ">", ">=", "<", "<=", "==" |
| threshold | REAL | NOT NULL | Numeric threshold |
| enabled | INTEGER | DEFAULT 1 | |
| created_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |
| updated_at | TEXT | DEFAULT CURRENT_TIMESTAMP | |

---

## 4. Backend REST API

Base URL: `http://localhost:8080/api`

### 4.1 Server Management

#### Create Server
```
POST /servers
Content-Type: application/json

{
  "name": "Production NATS",
  "url": "http://nats-prod:9999",
  "auth_type": "token",
  "auth_token": "secret-token"
}

Response: 201 Created
{
  "id": 1,
  "name": "Production NATS",
  "url": "http://nats-prod:9999",
  "auth_type": "token",
  "is_active": false,
  "created_at": "2024-01-15T10:00:00Z"
}
```

#### List Servers
```
GET /servers

Response: 200 OK
{
  "servers": [
    {
      "id": 1,
      "name": "Production NATS",
      "url": "http://nats-prod:9999",
      "auth_type": "token",
      "is_active": true
    }
  ]
}
```

#### Update Server
```
PUT /servers/:id
Content-Type: application/json

{
  "name": "Production NATS (Updated)",
  "auth_token": "new-token"
}

Response: 200 OK
```

#### Delete Server
```
DELETE /servers/:id

Response: 204 No Content
```

#### Activate Server
```
PUT /servers/:id/activate

Response: 200 OK
```

#### Test Connection
```
POST /servers/:id/test

Response: 200 OK
{
  "success": true,
  "server_name": "nats-prod-1",
  "version": "2.10.4"
}

Response: 400 Bad Request
{
  "success": false,
  "error": "Connection refused"
}
```

### 4.2 Label Management

#### List Label Categories
```
GET /servers/:id/labels

Response: 200 OK
{
  "categories": [
    {
      "id": 1,
      "name": "Environment",
      "rules": [
        { "id": 1, "label_value": "Production", "pattern": "^prod-.*" },
        { "id": 2, "label_value": "Staging", "pattern": "^staging-.*" }
      ]
    }
  ]
}
```

#### Create Label Category
```
POST /servers/:id/labels
Content-Type: application/json

{
  "name": "Environment"
}

Response: 201 Created
```

#### Create Label Rule
```
POST /labels/:category_id/rules
Content-Type: application/json

{
  "label_value": "Production",
  "pattern": "^prod-.*",
  "priority": 10
}

Response: 201 Created
```

#### Update Label Rule
```
PUT /rules/:id
Content-Type: application/json

{
  "pattern": "^production-.*"
}

Response: 200 OK
```

#### Delete Label Rule
```
DELETE /rules/:id

Response: 204 No Content
```

#### Assign Manual Label
```
POST /clients/:client_id/labels
Content-Type: application/json

{
  "category_id": 1,
  "label_value": "Production"
}

Response: 201 Created
```

### 4.3 Data Endpoints

#### Get Clients (with labels applied)
```
GET /servers/:id/clients?group_by=environment&search=order

Response: 200 OK
{
  "total": 1234,
  "clients": [
    {
      "cid": 1,
      "name": "order-service",
      "ip": "192.168.1.10",
      "version": "1.31.0",
      "lang": "go",
      "uptime": "5d2h",
      "in_msgs": 50000,
      "out_msgs": 48000,
      "subscriptions_count": 12,
      "labels": {
        "Environment": "Production",
        "Team": "Backend"
      }
    }
  ],
  "groups": {
    "Production": 847,
    "Staging": 312,
    "Development": 75
  }
}
```

#### Get Subscriptions
```
GET /servers/:id/subscriptions?search=orders

Response: 200 OK
{
  "total": 5678,
  "tree": {
    "orders": {
      "subscriber_count": 1245,
      "children": {
        "created": {
          "subscriber_count": 423,
          "children": {
            "domestic": { "subscriber_count": 198 },
            "intl": { "subscriber_count": 225 }
          }
        },
        "updated": { "subscriber_count": 412 },
        "cancelled": { "subscriber_count": 410 }
      }
    },
    "users": { "subscriber_count": 892 }
  }
}
```

#### Get Subscribers for Subject
```
GET /servers/:id/subscriptions/:subject/clients

Response: 200 OK
{
  "subject": "orders.created",
  "clients": [
    { "cid": 1, "name": "order-processor-1", "labels": { "Environment": "Production" } },
    { "cid": 2, "name": "analytics-service", "labels": { "Environment": "Production" } }
  ]
}
```

### 4.4 Alerts (P2)

#### List Alert Rules
```
GET /servers/:id/alerts

Response: 200 OK
{
  "alerts": [
    {
      "id": 1,
      "metric": "slow_consumers",
      "operator": ">",
      "threshold": 0,
      "enabled": true
    }
  ]
}
```

#### Create Alert Rule
```
POST /servers/:id/alerts
Content-Type: application/json

{
  "metric": "connections",
  "operator": ">",
  "threshold": 5000
}

Response: 201 Created
```

---

## 5. WebSocket Interface

### Connection
```
WS /ws/metrics?server_id=1
```

### Message Format (Server → Client)

```json
{
  "type": "varz",
  "timestamp": "2024-01-15T10:30:00Z",
  "data": {
    "server_name": "nats-prod-1",
    "connections": 1234,
    "in_msgs": 5000000,
    "cpu": 12.5,
    "mem": 536870912
  }
}
```

```json
{
  "type": "connz",
  "timestamp": "2024-01-15T10:30:00Z",
  "data": {
    "num_connections": 1234,
    "connections": [...]
  }
}
```

```json
{
  "type": "alert",
  "timestamp": "2024-01-15T10:30:00Z",
  "data": {
    "rule_id": 1,
    "metric": "slow_consumers",
    "current_value": 5,
    "threshold": 0,
    "message": "Slow consumers detected: 5"
  }
}
```

### Client Commands (Client → Server)

```json
{
  "action": "subscribe",
  "types": ["varz", "connz", "subz"]
}
```

```json
{
  "action": "set_interval",
  "interval_ms": 5000
}
```

---

## 6. UI Wireframes

### 6.1 Connection Screen

```
+----------------------------------------------------+
|              NATSWatch                             |
|                                                    |
|   Connect to your NATS server                      |
|                                                    |
|   Server URL:                                      |
|   +----------------------------------------------+ |
|   | http://nats-server.example.com:9999          | |
|   +----------------------------------------------+ |
|                                                    |
|   Authentication:  ( ) None                        |
|                    (*) Token                       |
|                    ( ) Username & Password         |
|                                                    |
|   Token:                                           |
|   +----------------------------------------------+ |
|   | ************************************         | |
|   +----------------------------------------------+ |
|                                                    |
|          [ Test Connection ]  [ Connect ]          |
|                                                    |
|   Saved Servers:                                   |
|   +----------------------------------------------+ |
|   | * Production NATS  (nats-prod:9999)          | |
|   |   Staging NATS     (nats-stage:9999)         | |
|   +----------------------------------------------+ |
+----------------------------------------------------+
```

### 6.2 Dashboard

```
+---------------------------------------------------------------+
| NATSWatch    [Overview] [Clients] [Subscriptions] [Settings]  |
+---------------------------------------------------------------+
|                                                               |
|  Server: Production NATS          Status: [====] Healthy      |
|  Version: 2.10.4    Running for: 14 days                      |
|                                                               |
+---------------------------------------------------------------+
|                                                               |
|  +-------------+  +-------------+  +-------------+            |
|  | Connected   |  | Messages    |  | Messages    |            |
|  | Clients     |  | Received    |  | Sent        |            |
|  |   1,234     |  |  50K/sec    |  |  48K/sec    |            |
|  | [?] tooltip |  | [?] tooltip |  | [?] tooltip |            |
|  +-------------+  +-------------+  +-------------+            |
|                                                               |
|  +-------------+  +-------------+                             |
|  | Memory      |  | CPU         |                             |
|  | Usage       |  | Usage       |                             |
|  |  512 MB     |  |   12%       |                             |
|  +-------------+  +-------------+                             |
|                                                               |
+---------------------------------------------------------------+
```

### 6.3 Client Visualization

```
+---------------------------------------------------------------+
| Clients    Group by: [Environment v]  Search: [_____________] |
+---------------------------------------------------------------+
| Filter: [x] Production  [x] Staging  [ ] Development          |
+---------------------------------------------------------------+
|                                                               |
|  PRODUCTION (847 clients)                                     |
|  +----------------------------------------------------------+ |
|  | +----------------+ +----------------+ +----------------+  | |
|  | | api-gateway    | | order-service  | | user-service   |  | |
|  | | v1.31.0        | | v1.31.0        | | v1.28.0 (!)    |  | |
|  | | 192.168.1.10   | | 192.168.1.11   | | 192.168.1.12   |  | |
|  | | 12 subs        | | 8 subs         | | 5 subs         |  | |
|  | +----------------+ +----------------+ +----------------+  | |
|  +----------------------------------------------------------+ |
|                                                               |
|  STAGING (312 clients)                                        |
|  +----------------------------------------------------------+ |
|  | +----------------+ +----------------+                     | |
|  | | api-gateway    | | order-service  |                     | |
|  | | v2.0.0-beta    | | v2.0.0-beta    |                     | |
|  | +----------------+ +----------------+                     | |
|  +----------------------------------------------------------+ |
|                                                               |
|  [+ Add Label Category]  [Manage Label Rules]                 |
+---------------------------------------------------------------+
```

### 6.4 Subscription Hierarchy

```
+---------------------------------------------------------------+
| Subscriptions         Search: [orders.*___]   [Clear Filters] |
+---------------------------------------------------------------+
|                                                               |
|  [-] orders                           (1,245 subscribers)     |
|      [-] orders.created               (423 subscribers)       |
|          [+] orders.created.domestic  (198 subscribers)       |
|          [+] orders.created.intl      (225 subscribers)       |
|      [+] orders.updated               (412 subscribers)       |
|      [+] orders.cancelled             (410 subscribers)       |
|                                                               |
|  [+] users                            (892 subscribers)       |
|  [+] inventory                        (567 subscribers)       |
|  [+] notifications                    (334 subscribers)       |
|                                                               |
+---------------------------------------------------------------+
|                                                               |
|  Selected: orders.created                                     |
|  +----------------------------------------------------------+ |
|  | Subscribed Clients (423):                                 | |
|  | - order-processor-1 (Production)                          | |
|  | - order-processor-2 (Production)                          | |
|  | - analytics-service (Production)                          | |
|  | - order-processor-staging (Staging)                       | |
|  | [View all...]                                             | |
|  +----------------------------------------------------------+ |
+---------------------------------------------------------------+
```

---

## 7. Frontend Components

```
src/
├── pages/
│   ├── ConnectionPage.tsx
│   ├── DashboardPage.tsx
│   ├── ClientsPage.tsx
│   ├── SubscriptionsPage.tsx
│   └── SettingsPage.tsx
├── components/
│   ├── layout/
│   │   ├── Navbar.tsx
│   │   └── Sidebar.tsx
│   ├── dashboard/
│   │   ├── MetricCard.tsx
│   │   ├── ServerStatus.tsx
│   │   └── HealthIndicator.tsx
│   ├── clients/
│   │   ├── ClientCard.tsx
│   │   ├── ClientGrid.tsx
│   │   ├── ClientTable.tsx
│   │   ├── LabelFilter.tsx
│   │   └── GroupBySelector.tsx
│   ├── subscriptions/
│   │   ├── SubjectTree.tsx
│   │   ├── SubjectNode.tsx
│   │   └── SubscriberList.tsx
│   ├── connection/
│   │   ├── ServerForm.tsx
│   │   ├── AuthSelector.tsx
│   │   └── SavedServerList.tsx
│   └── shared/
│       ├── SearchBar.tsx
│       ├── Tooltip.tsx
│       ├── LoadingSpinner.tsx
│       └── ErrorBoundary.tsx
├── hooks/
│   ├── useWebSocket.ts
│   ├── useNatsData.ts
│   └── useLocalStorage.ts
├── services/
│   ├── api.ts
│   └── websocket.ts
├── types/
│   ├── nats.ts
│   ├── server.ts
│   └── label.ts
└── utils/
    ├── formatters.ts
    └── labelMatcher.ts
```

---

## 8. TypeScript Types

```typescript
// types/nats.ts
interface VarzData {
  server_id: string;
  server_name: string;
  version: string;
  uptime: string;
  mem: number;
  cpu: number;
  connections: number;
  in_msgs: number;
  out_msgs: number;
  slow_consumers: number;
}

interface Connection {
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
  subscriptions: string[];
}

interface ConnzData {
  num_connections: number;
  connections: Connection[];
}

// types/server.ts
type AuthType = 'none' | 'token' | 'userpass';

interface Server {
  id: number;
  name: string;
  url: string;
  auth_type: AuthType;
  is_active: boolean;
  created_at: string;
}

interface ServerCreateRequest {
  name: string;
  url: string;
  auth_type: AuthType;
  auth_token?: string;
  auth_username?: string;
  auth_password?: string;
}

// types/label.ts
interface LabelCategory {
  id: number;
  name: string;
  rules: LabelRule[];
}

interface LabelRule {
  id: number;
  label_value: string;
  pattern: string;
  priority: number;
}

interface ClientWithLabels extends Connection {
  labels: Record<string, string>;
}

// types/websocket.ts
type WSMessageType = 'varz' | 'connz' | 'subz' | 'alert';

interface WSMessage<T> {
  type: WSMessageType;
  timestamp: string;
  data: T;
}
```