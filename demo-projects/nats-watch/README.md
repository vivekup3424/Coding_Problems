# NATSWatch

Web UI dashboard with alerts to monitor NATS Server. Runs locally, connects to any remote NATS monitoring endpoint.

## Overview

NATSWatch provides a real-time web dashboard for monitoring NATS server health, connections, subscriptions, and message throughput. Runs locally with no login required — just point it at a NATS monitoring endpoint (e.g. `http://kioti-nats-1.keus.in:9999`) and go. Built with Claude Code as a collaborative coding exercise.

## Reference Projects

### Official Documentation
- [NATS Server Monitoring](https://docs.nats.io/running-a-nats-service/nats_admin/monitoring) - Official docs for the monitoring endpoints (`/varz`, `/connz`, `/subz`, `/jsz`, etc.)
- [Keus NATS Instance](http://kioti-nats-1.keus.in:9999/leafz?subs=0) - Live NATS server monitoring endpoint for reference/testing

### Existing UI Projects
We studied three existing NATS UI projects and picked the best ideas from each:

### [Alleny244/Nats-UI](https://github.com/Alleny244/Nats-UI)
React + FastAPI dashboard for JetStream monitoring.
- **Take**: Message metrics display (total, processed, unprocessed), interactive tables with sequence numbers, pie chart visualizations
- **Skip**: JetStream-only focus (we want core NATS server monitoring too), FastAPI backend (we'll use Go/Node)

### [mdawar/nats-dashboard](https://github.com/mdawar/nats-dashboard)
Static PWA that hits NATS monitoring endpoints directly from the browser.
- **Take**: Zero-backend architecture idea (browser → NATS `/varz`, `/connz`, `/subz` endpoints), multi-server support, PWA offline capability, clean Tailwind UI
- **Skip**: No auth (we need it), no alerts, no historical data, relies on NATS CORS/JSONP which limits deployment

### [sphqxe/NATS-WebUI](https://github.com/sphqxe/NATS-WebUI)
Rust + Vue app with WebSocket-based real-time message streaming.
- **Take**: WebSocket live updates, subject hierarchy tree view, multi-client support, SQLite for persisting server configs
- **Skip**: Rust backend complexity (overkill for our scope), no auth, no alerting

## What NATSWatch Adds (Our Differentiators)

| Feature | Nats-UI | nats-dashboard | NATS-WebUI | **NATSWatch** |
|---|---|---|---|---|
| Alerts | No | No | No | **Yes** |
| Core server metrics | No | Yes | Yes | **Yes** |
| Client version site map | No | No | No | **Yes** |
| JetStream metrics | Yes | No | No | **Yes** |
| Real-time updates | Yes | Polling | WebSocket | **WebSocket/SSE** |
| Historical data | No | No | No | **Yes (basic)** |
| Multi-server | No | Yes | Yes | **Yes** |
| Local-first (no login) | No | Yes | No | **Yes** |

## Planned Features

### P0 - Core (Must Have)
- **Connection Setup** - Welcome screen prompts for NATS monitoring URL (e.g. `http://kioti-nats-1.keus.in:9999`), no login needed
- **Server Overview (Welcome Screen)** - Landing page shows live `/varz` data: server name, version, uptime, connections, messages in/out, bytes, slow consumers, memory, CPU
- **Client Site Map** - Built from `/connz` data: visual map of all connected clients grouped by client version, language, IP — answers "what versions are our clients running?" at a glance
- **Subscriptions View** - Subject hierarchy tree from `/subz`

### P1 - Important
- **Alerts** - Configurable thresholds (e.g. connections > N, slow consumers > 0, memory usage) with in-app notifications
- **JetStream Monitoring** - Streams, consumers, and message counts from `/jsz`
- **Multi-server Support** - Add/switch between multiple NATS server connections

### P2 - Nice to Have
- **Basic Historical Data** - Store snapshots of metrics over time, show trend charts
- **PWA Support** - Installable, works offline (shows last-known state)
- **Dark Mode**

## Tech Stack

| Layer | Choice | Rationale |
|---|---|---|
| Frontend | **React + Vite + TypeScript** | Fast dev, strong ecosystem, familiar |
| Styling | **Tailwind CSS** | Utility-first, rapid UI building |
| Charts | **Recharts** or **Chart.js** | Lightweight, React-friendly |
| Backend | **Go (net/http + gorilla/websocket)** | Fast, small binary, natural fit for NATS ecosystem |
| Database | **SQLite** | Zero-config, stores server configs + alert rules + metric snapshots |
| Containerization | **Docker + Docker Compose** | Easy local dev and deployment |

## Architecture

```
┌─────────────┐         ┌──────────────┐        ┌───────────────────────────────┐
│   React UI  │◄──WSS──►│   Go Backend │◄──HTTP──►│  NATS Server(s)               │
│  (Vite/TS)  │         │              │        │  e.g. kioti-nats-1.keus.in:9999│
└─────────────┘         │  - WebSocket │        │  /varz /connz /subz /jsz      │
                        │  - Alerts    │        └───────────────────────────────┘
                        │  - Poller    │
                        │              │        ┌─────────────────┐
                        │              │◄──────►│   SQLite DB     │
                        └──────────────┘        │  configs/alerts │
                                                └─────────────────┘
```

**Flow:**
1. User opens the app → **Welcome screen** asks for NATS monitoring URL (no login)
2. **Go backend** connects to the NATS monitoring endpoint and polls `/varz`, `/connz`, `/subz`, `/jsz` on a configurable interval
3. **Welcome/Home page** displays live `/varz` data — server health at a glance
4. **Client Site Map** page parses `/connz` to build a visual map of connected clients grouped by version, language, and IP — answering observability questions like "what client versions are deployed?"
5. **WebSocket** pushes live metric updates to the frontend
6. **Alert engine** evaluates rules against incoming metrics and fires notifications
7. **SQLite** persists server configs, alert rules, and optional metric snapshots

## Build Plan

### Phase 1: Scaffolding (~15 min)
- [ ] Init Go backend with module, basic HTTP server, health endpoint
- [ ] Init React frontend with Vite + TypeScript + Tailwind
- [ ] Docker Compose for both services
- [ ] Verify end-to-end connectivity

### Phase 2: Connection + Welcome Screen (~25 min)
- [ ] Frontend: Welcome/connect screen — input field for NATS monitoring URL (e.g. `http://kioti-nats-1.keus.in:9999`)
- [ ] Backend: API to accept + validate NATS monitoring URL, persist to SQLite
- [ ] Backend: NATS poller service hitting `/varz`
- [ ] Backend: WebSocket endpoint streaming `/varz` to frontend
- [ ] Frontend: Home dashboard showing live `/varz` cards (server name, version, uptime, connections, messages in/out, bytes, slow consumers, memory, CPU)

### Phase 3: Client Site Map from `/connz` (~30 min)
- [ ] Backend: Poll `/connz` with `subs=detail` to get full connection info
- [ ] Backend: Parse and group connections by client version, client language, and IP
- [ ] Frontend: Site map view — visual grouping of clients by version (e.g. treemap, grouped cards, or table with filters)
- [ ] Frontend: Drill-down into a client group to see individual connection details (IP, subscriptions, msgs sent/recv, uptime)
- [ ] Frontend: Highlight outdated client versions or anomalies

### Phase 4: Subscriptions + Alerts (~25 min)
- [ ] Backend: Poll `/subz` for subscription data
- [ ] Frontend: Subscriptions tree view by subject hierarchy
- [ ] Backend: Alert rules CRUD API + SQLite table
- [ ] Backend: Alert evaluation engine (runs on each poll cycle)
- [ ] Frontend: Alert configuration page + notification toasts

### Phase 5: JetStream + Multi-server (~20 min)
- [ ] Backend: `/jsz` polling, streams/consumers data
- [ ] Frontend: JetStream tab with stream details
- [ ] Backend + Frontend: Add/manage multiple NATS server connections (switch between servers)

### Phase 6: Polish (~10 min)
- [ ] Error handling and loading states
- [ ] Responsive layout
- [ ] README with setup instructions

## Estimated Time

1-3 hours

## Status

Project kickoff scheduled for Friday.
