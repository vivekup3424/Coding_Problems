# Product Requirements Document (PRD)
## NATSWatch - NATS Server Monitoring Dashboard

---

### Document Info
| Field | Value |
|-------|-------|
| **Product Name** | NATSWatch |
| **Version** | 1.0 |
| **Author** | Product Team |
| **Status** | Draft |
| **Last Updated** | 2026-02-06 |

---

## 1. Executive Summary

**NATSWatch** is a user-friendly web dashboard for monitoring NATS servers in real-time. Designed for **non-technical users** (including support staff with no NATS knowledge), it provides intuitive visibility into server health, client connections, and subscription hierarchies.

**Problem Statement:** Teams running NATS infrastructure need a simple way to monitor server health and understand client connections. Support staff often need to investigate issues but lack NATS expertise. Existing tools are either too technical, JetStream-only, or require complex setup.

**Solution:** An intuitive, easy-to-use dashboard that connects to any NATS server (with token or user/password authentication), visualizes connected clients with flexible label-based categorization, and displays subscription hierarchies in a clear, understandable format.

---

## 2. Goals & Success Metrics

### Goals
1. **User-friendly for non-technical users** — Support staff with no NATS knowledge can use it effectively
2. **Flexible authentication** — Connect with token auth or user/password as required by the NATS server
3. **Visual client insights** — Categorize and visualize connected clients by customizable labels
4. **Clear subscription visualization** — Display subscription hierarchy in an intuitive, explorable format

### Success Metrics (KPIs)
| Metric | Target |
|--------|--------|
| Time from install to first dashboard view | < 2 minutes |
| Non-technical user task completion rate | > 90% without assistance |
| Time to find a specific client | < 30 seconds |
| Client visualization accuracy | 100% of `/connz` data represented |
| P95 UI latency for metric refresh | < 200ms |

---

## 3. User Personas

### Persona 1: Support Staff (Primary)
- **Name:** Anita
- **Role:** Customer Support / L1 Support Engineer
- **Technical Level:** No NATS knowledge; basic IT skills
- **Goals:** Quickly check if NATS server is healthy, identify which clients are connected, understand subscription structure when troubleshooting customer issues
- **Pain Points:** Current tools require CLI expertise; doesn't understand NATS terminology; needs visual, self-explanatory interface

### Persona 2: Platform Engineer (Secondary)
- **Name:** Priya
- **Role:** SRE / Platform Engineer
- **Technical Level:** NATS-savvy; needs detailed metrics
- **Goals:** Monitor NATS cluster health, identify slow consumers, track client version drift, categorize clients by environment/team/service
- **Pain Points:** Currently SSHs into servers and curls `/varz` manually; no unified view of client categorization

### Persona 3: Backend Developer (Tertiary)
- **Name:** Raj
- **Role:** Backend Developer
- **Technical Level:** Knows application code, learning NATS
- **Goals:** Debug connection issues, verify subscriptions, check message flow during development
- **Pain Points:** Hard to correlate client connections with app instances; lacks visibility into subscription hierarchy

---

## 4. User Stories & Requirements

### P0 - Must Have (Core)

| ID | User Story | Acceptance Criteria |
|----|------------|---------------------|
| US-01 | As a support user, I want a simple, intuitive interface so I can use it without NATS knowledge | Clean UI with tooltips, plain-language labels, no jargon; guided onboarding flow |
| US-02 | As a user, I want to connect to NATS with token OR user/password authentication | Connection form supports: URL + Token auth, OR URL + Username + Password; auto-detects auth type if possible |
| US-03 | As a user, I want to visualize all connected clients with categorization by labels | Interactive client visualization (cards/graph/table); filter and group by: client name, version, language, IP, custom labels |
| US-04 | As a user, I want to view subscription hierarchy visually so I can understand topic structure | Interactive tree/graph view of subjects from `/subz`; expandable nodes; search/filter capability |

### P1 - Important

| ID | User Story | Acceptance Criteria |
|----|------------|---------------------|
| US-05 | As a user, I want to see server health at a glance with simple status indicators | Dashboard shows health status with color-coded indicators (green/yellow/red); plain-language descriptions |
| US-06 | As a user, I want to define custom labels for client categorization | Create custom label categories (e.g., "Environment", "Team", "Service"); assign labels based on client name patterns or manual tagging |
| US-07 | As a user, I want to search and filter clients easily | Search by client name, IP, subscription; filter by any label category |
| US-08 | As a user, I want to monitor multiple NATS servers | Add/switch between saved server connections with their respective auth credentials |

### P2 - Nice to Have

| ID | User Story | Acceptance Criteria |
|----|------------|---------------------|
| US-09 | As a user, I want to configure alerts for threshold breaches | Alert rules CRUD; in-app notifications; thresholds for connections, slow consumers, memory |
| US-10 | As a user, I want JetStream visibility | JetStream tab showing streams, consumers, message counts from `/jsz` |
| US-11 | As a user, I want dark mode for comfortable viewing | Theme toggle; persisted preference |

---

## 5. Functional Requirements

### 5.1 User Experience (Non-Technical Focus)
- **FR-01:** UI shall use plain-language labels (avoid NATS jargon where possible)
- **FR-02:** All technical terms shall have tooltips with simple explanations
- **FR-03:** Error messages shall be actionable and user-friendly (not raw error codes)
- **FR-04:** UI shall provide guided onboarding for first-time users

### 5.2 Connection & Authentication
- **FR-05:** System shall accept NATS monitoring endpoint URL (format: `http(s)://host:port`)
- **FR-06:** System shall support **Token-based authentication** (Authorization header with token)
- **FR-07:** System shall support **User/Password authentication** (Basic auth or NATS credentials)
- **FR-08:** Connection form shall allow user to choose auth method: None, Token, or User/Password
- **FR-09:** System shall validate endpoint connectivity before saving
- **FR-10:** Credentials shall be stored securely (encrypted in SQLite)
- **FR-11:** System shall support multiple saved server connections with easy switching

### 5.3 Client Visualization & Categorization
- **FR-12:** System shall display all connected clients from `/connz` in a visual format (cards, table, or graph)
- **FR-13:** System shall support grouping clients by built-in labels: client name, version, language, IP address
- **FR-14:** System shall support **custom label categories** (e.g., "Environment", "Team", "Service", "Region")
- **FR-15:** Custom labels shall be assignable via: pattern matching on client name, manual tagging, or import
- **FR-16:** Users shall be able to filter and search clients by any label
- **FR-17:** Client visualization shall support drill-down to individual connection details
- **FR-18:** System shall highlight anomalies (e.g., outdated versions, high message rates)

### 5.4 Subscription Hierarchy Visualization
- **FR-19:** Subscriptions View shall render subject hierarchy as an **interactive tree or graph**
- **FR-20:** Tree nodes shall be expandable/collapsible
- **FR-21:** Users shall be able to search/filter subscriptions by subject pattern
- **FR-22:** Subscription view shall show subscriber count per subject
- **FR-23:** Clicking a subject shall show which clients are subscribed

### 5.5 Data Polling & Streaming
- **FR-24:** Backend shall poll NATS endpoints (`/varz`, `/connz`, `/subz`, `/jsz`) at configurable intervals (default: 5s)
- **FR-25:** Backend shall push metric updates to frontend via WebSocket
- **FR-26:** System shall handle endpoint unavailability gracefully with retry logic and user-friendly UI indication

### 5.6 Alerting (P2)
- **FR-27:** System shall support alert rules with conditions: `metric` `operator` `threshold`
- **FR-28:** Supported metrics: `connections`, `slow_consumers`, `memory_mb`, `cpu_percent`, `in_msgs_rate`, `out_msgs_rate`
- **FR-29:** Triggered alerts shall display as in-app toast notifications

### 5.7 JetStream (P2)
- **FR-30:** JetStream tab shall display streams with: name, subjects, message count, byte size
- **FR-31:** JetStream tab shall display consumers per stream with lag metrics

---

## 6. Non-Functional Requirements

| Category | Requirement |
|----------|-------------|
| **Usability** | Non-technical users shall be able to complete core tasks without training |
| **Usability** | All technical terms shall have contextual help (tooltips, info icons) |
| **Usability** | Error states shall provide clear, actionable guidance |
| **Usability** | Responsive design for 1024px+ screens |
| **Performance** | Dashboard shall render within 500ms of data receipt |
| **Performance** | Backend shall handle polling 10 NATS servers concurrently |
| **Performance** | Client visualization shall handle 10,000+ clients with virtualization |
| **Reliability** | System shall reconnect WebSocket within 5s on disconnect |
| **Security** | Auth credentials shall be encrypted at rest (AES-256) |
| **Security** | Credentials shall never be logged or exposed in API responses |
| **Security** | HTTPS support for NATS monitoring endpoints |
| **Portability** | Runs via Docker Compose on Linux/macOS/Windows |

---

## 7. Technical Specification

For detailed technical documentation including:
- System architecture and tech stack
- Data models (SQLite schema)
- REST API endpoints and contracts
- WebSocket interface
- UI wireframes
- Frontend component structure
- TypeScript type definitions

See **[INTERFACE_SPEC.md](./INTERFACE_SPEC.md)**

---

## 8. Milestones & Timeline

| Phase | Deliverable | Duration |
|-------|-------------|----------|
| **Phase 1** | Project scaffolding (Go + React + Docker) | ~15 min |
| **Phase 2** | Welcome screen + live `/varz` dashboard | ~25 min |
| **Phase 3** | Client Site Map from `/connz` | ~30 min |
| **Phase 4** | Subscriptions view + Alerts engine | ~25 min |
| **Phase 5** | JetStream tab + Multi-server | ~20 min |
| **Phase 6** | Polish, error handling, docs | ~10 min |
| **Total** | MVP Release | **~2-3 hours** |

---

## 9. Risks & Mitigations

| Risk | Impact | Likelihood | Mitigation |
|------|--------|------------|------------|
| NATS endpoint CORS restrictions | High | Medium | Go backend proxies all requests |
| Large `/connz` response (10K+ clients) | Medium | Low | Pagination, virtualized lists |
| SQLite concurrency limits | Low | Low | Single writer pattern, WAL mode |
| WebSocket disconnects on network issues | Medium | Medium | Auto-reconnect with exponential backoff |

---

## 10. Out of Scope (v1.0)

- Multi-user login / role-based access control (single-user local app)
- Cloud-hosted deployment
- Mobile-native apps
- Custom dashboards / widgets
- Slack/PagerDuty alert integrations (future consideration)
- NATS cluster mode visualization
- Message publishing/subscribing (read-only monitoring only)
- Certificate-based authentication (TLS client certs)

---

## 11. Open Questions

1. **Polling interval:** Should default be 5s or configurable per-server?
2. **Label import:** Should we support importing labels from CSV or external systems?
3. **Credential storage:** Use OS keychain vs encrypted SQLite for auth credentials?
4. **Default label categories:** Should we pre-create common categories (Environment, Team, Service)?
5. **Subscription visualization:** Tree view vs graph view vs both as options?

---

## 12. Appendix

### NATS Monitoring Endpoints Reference
| Endpoint | Description |
|----------|-------------|
| `/varz` | Server statistics (connections, memory, CPU, messages) |
| `/connz` | Active client connections with details |
| `/subz` | Subscription information by subject |
| `/jsz` | JetStream streams and consumers |
| `/routez` | Cluster route information |
| `/leafz` | Leaf node connections |

### Competitive Landscape
| Project | Strengths | Gaps NATSWatch Fills |
|---------|-----------|---------------------|
| Alleny244/Nats-UI | Good JetStream UX | No core metrics, no alerts |
| mdawar/nats-dashboard | Zero-backend, PWA | No alerts, no historical data |
| sphqxe/NATS-WebUI | Real-time WebSocket | No alerts, no client version map |

---

**Document Status:** Ready for stakeholder review
**Next Steps:** Finalize open questions -> Begin Phase 1 implementation
