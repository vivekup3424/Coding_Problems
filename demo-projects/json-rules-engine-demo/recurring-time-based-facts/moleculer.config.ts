import { Errors, ServiceBroker } from "moleculer";
import { getchannelsmiddleware } from "./middleware";
import { contextInjectorMiddleware } from "./contextInjectorMiddleware";
const TracingMiddleware = require("@moleculer/channels").Tracing;
export const brokerConfig = {
	namespace: "WEEKND",
	nodeID: "node-1",
	metadata: {},
	logger: {
		type: "Console",
		options: {
			// Using colors on the output
			colors: true,
			// Print module names with different colors (like docker-compose for containers)
			moduleColors: false,
			// Line formatter. It can be "json", "short", "simple", "full", a `Function` or a template string like "{timestamp} {level} {nodeID}/{mod}: {msg}"
			formatter: "full",
			// Custom object printer. If not defined, it uses the `util.inspect` method.
			objectPrinter: null,
			// Auto-padding the module name in order to messages begin at the same column.
			autoPadding: true,
		},
	},

	transporter: {
		type: "NATS",
		options: {
		  url: "nats://172.24.128.1:6969",
		//   token: "keus-iot-platform",
		},
	  },
	

	// Define a cacher.
	// More info: https://moleculer.services/docs/0.14/caching.html
    cacher: null,

	// Define a serializer.
	// Available values: "JSON", "Avro", "ProtoBuf", "MsgPack", "Notepack", "Thrift".
	// More info: https://moleculer.services/docs/0.14/networking.html#Serialization
	serializer: "JSON",

	// Number of milliseconds to wait before reject a request with a RequestTimeout error. Disabled: 0
	requestTimeout: 10 * 1000,

	// Retry policy settings. More info: https://moleculer.services/docs/0.14/fault-tolerance.html#Retry
	retryPolicy: {
		enabled: true,
		// Count of retries
		retries: 5,
		// First delay in milliseconds.
		delay: 100,
		// Maximum delay in milliseconds.
		maxDelay: 1000,
		// Backoff factor for delay. 2 means exponential backoff.
		factor: 2,
		// A function to check failed requests.
		check: (err:any) =>
			err && err instanceof Errors.MoleculerRetryableError && !!err.retryable,
	},

	// Limit of calling level. If it reaches the limit, broker will throw an MaxCallLevelError error. (Infinite loop protection)
	maxCallLevel: 100,

	// Number of seconds to send heartbeat packet to other nodes.
	heartbeatInterval: 10,
	// Number of seconds to wait before setting node to unavailable status.
	heartbeatTimeout: 30,

	// Cloning the params of context if enabled. High performance impact, use it with caution!
	contextParamsCloning: false,

	// Tracking requests and waiting for running requests before shuting down. More info: https://moleculer.services/docs/0.14/context.html#Context-tracking
	tracking: {
		// Enable feature
		enabled: false,
		// Number of milliseconds to wait before shuting down the process.
		shutdownTimeout: 5000,
	},

	// Disable built-in request & emit balancer. (Transporter must support it, as well.). More info: https://moleculer.services/docs/0.14/networking.html#Disabled-balancer
	disableBalancer: false,

	// Settings of Service Registry. More info: https://moleculer.services/docs/0.14/registry.html
	registry: {
		// Define balancing strategy. More info: https://moleculer.services/docs/0.14/balancing.html
		// Available values: "RoundRobin", "Random", "CpuUsage", "Latency", "Shard"
		strategy: "RoundRobin",
		// Enable local action call preferring. Always call the local action instance if available.
		preferLocal: true,
	},

	// Settings of Circuit Breaker. More info: https://moleculer.services/docs/0.14/fault-tolerance.html#Circuit-Breaker
	circuitBreaker: {
		// Enable feature
		enabled: true,
		// Threshold value. 0.5 means that 50% should be failed for tripping.
		threshold: 0.5,
		// Minimum request count. Below it, CB does not trip.
		minRequestCount: 20,
		// Number of seconds for time window.
		windowTime: 60,
		// Number of milliseconds to switch from open to half-open state
		halfOpenTime: 10 * 1000,
		// A function to check failed requests.
		check: (err:any) => err && err instanceof Errors.MoleculerError && err.code >= 500,
	},

	// Settings of bulkhead feature. More info: https://moleculer.services/docs/0.14/fault-tolerance.html#Bulkhead
	bulkhead: {
		// Enable feature.
		enabled: false,
		// Maximum concurrent executions.
		concurrency: 10,
		// Maximum size of queue
		maxQueueSize: 100,
	},

	// Enable action & event parameter validation. More info: https://moleculer.services/docs/0.14/validating.html
	validator: true,


	// Enable/disable built-in metrics function. More info: https://moleculer.services/docs/0.14/metrics.html
	metrics: {
		enabled: false,
		// Available built-in reporters: "Console", "CSV", "Event", "Prometheus", "Datadog", "StatsD"
		reporter: {
			type: "Console",
		},
	},

	// Enable built-in tracing function. More info: https://moleculer.services/docs/0.14/tracing.html
	tracing: {
		enabled: true,
		// Available built-in exporters: "Console", "Datadog", "Event", "EventLegacy", "Jaeger", "Zipkin"
		exporter: {
			type: "console", // Console exporter is only for development!
		},
	},

	// Register custom middlewares
	middlewares: [getchannelsmiddleware({namespace:"WEEKND"}), TracingMiddleware(), contextInjectorMiddleware ],

	// Register custom REPL commands.
	replCommands: null,
	// created(broker: ServiceBroker): void {},
	// async started(broker: ServiceBroker): Promise<void> {},
	// async stopped(broker: ServiceBroker): Promise<void> {},

};