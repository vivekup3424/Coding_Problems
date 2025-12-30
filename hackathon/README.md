Working on rules engine system for camera motion events. Incoming camera motion events are evaluated by a rules engine (json-rules-engine) and the outcomes can trigger downstream actions.

## Camera motion data schema (DBSchema payload)
- _id: unique id
- event_id: e.g., cameras.motion.person
- event_type: e.g., cameras
- hour_of_day: number (0-23)
- day_of_week: number (0-6)
- count_last_24h / count_last_7d / count_last_30d / count_last_90d / count_all_time: numbers
- last_occurred: number (timestamp)

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
2) Publish a sample camera motion event with nats CLI (using nats-box):
	- `docker run --rm --network=host natsio/nats-box:latest nats pub camera.motion '{"_id":"evt-1","event_id":"cameras.motion.person","event_type":"cameras","hour_of_day":12,"day_of_week":2,"count_last_24h":5,"count_last_7d":18,"count_last_30d":42,"count_last_90d":90,"count_all_time":120,"last_occurred":1735550400000}'`
3) Subscribe to see messages:
	- `docker run --rm --network=host natsio/nats-box:latest nats sub camera.motion`
4) Stop NATS when done:
	- `docker compose down`

## Publish test events from the repo (TypeScript script)
- Run once (uses env for servers/subject):
	- `npx tsx scripts/publish-event.ts`
- Optional overrides:
	- `NATS_SERVERS="nats://localhost:4222" NATS_SUBJECT="camera.motion" EVENT_ID="evt-99" EVENT_TYPE="cameras" COUNT_LAST_24H=7 COUNT_LAST_7D=20 COUNT_LAST_30D=60 COUNT_LAST_90D=140 COUNT_ALL_TIME=300 LAST_OCCURRED=1735550400000 npx tsx scripts/publish-event.ts`

## Sample camera motion event
```json
{
	"_id": "evt-1",
	"event_id": "cameras.motion.person",
	"event_type": "cameras",
	"hour_of_day": 12,
	"day_of_week": 2,
	"count_last_24h": 5,
	"count_last_7d": 18,
	"count_last_30d": 42,
	"count_last_90d": 90,
	"count_all_time": 120,
	"last_occurred": 1735550400000
}
```