Working on rules engine system for camera motion events. Incoming camera motion events are evaluated by a rules engine (json-rules-engine) and the outcomes can trigger downstream actions.

## Event schema
- eventId: string (e.g., cameras.motion.person)
- eventType: string (e.g., cameras)
- zone: string (e.g., front-door, backyard)
- timestamp: Date

## Event-info enrichment
- Before rules run, the service POSTs to http://localhost:3000/api/events/query with body `{ eventId, eventType, zone, timestamp }`.
- Expected response `{ success, data: { occurrence (0-3), dismissible (bool), overallCount (number) } }`.
- If `dismissible` is true, the event is skipped.
- Facts passed to rules include `occurrence`, `dismissible`, `overallCount` in addition to the event fields.

## Quick start
1) Install deps: `npm install`
2) Run dev server: `npm run dev`

Env vars:
- `NATS_SERVERS` (default `nats://localhost:4222`)
- `NATS_SUBJECT` (default `camera.motion`)
- `NATS_QUEUE` (optional queue group)
- `RULES_PATH` (default `src/rules/rules.json`)

## Rules file
Rules live at `src/rules/rules.json`. Each rule follows json-rules-engine format:
- `name`: rule label
- `conditions`: `all`/`any` arrays of condition objects
- `event`: `{ type, params? }` emitted when conditions match
- `priority` and other json-rules-engine fields are supported

Example rule (see `src/rules/rules.json`): alert when motion detected while home state is Away.

## NATS flow
- Subscribe to `NATS_SUBJECT` for camera motion events
- Decode JSON payload and validate against the schema above
- Run json-rules-engine with the event as facts
- Emit matched rule events (currently logged; can be published downstream)

## Local NATS (Docker) and nats CLI
1) Start NATS server (JetStream enabled) detached:
	- `docker compose up -d nats`
	- Monitoring UI at http://localhost:8222
2) Publish a sample event with nats CLI (using nats-box):
	- `docker run --rm --network=host natsio/nats-box:latest nats pub p1.fact.state.changed.something '{"eventId":"cameras.motion.person","eventType":"cameras","zone":"front-door","timestamp":"2025-12-30T12:00:00Z"}'`
3) Subscribe to see messages:
	- `docker run --rm --network=host natsio/nats-box:latest nats sub p1.fact.state.changed.something`
4) Stop NATS when done:
	- `docker compose down`

## Publish test events from the repo (TypeScript script)
- Run once:
	- `npx tsx scripts/publish-event.ts`
- Publishes with current time's hour/day and hardcoded counts

## Sample event
```json
{
	"eventId": "cameras.motion.person",
	"eventType": "cameras",
	"zone": "front-door",
	"timestamp": "2025-12-30T12:00:00Z"
}
```

## Real-time UI Dashboard
1) Start the UI server:
	- `npm run ui:dev`
	- Dashboard accessible at http://localhost:8080
2) Start the rules engine:
	- `npm run dev` (in another terminal)
3) Publish test events:
	- `npx tsx scripts/publish-event.ts`
	- Events will appear in real-time on the dashboard
4) Features:
	- Live event stream with color-coded severity badges
	- Occurrence level indicators (Very Rare, Rare, Occasional, Common)
	- Dismissible events clearly marked
	- Anomaly detection highlights
	- Auto-scrolling with last 20 events