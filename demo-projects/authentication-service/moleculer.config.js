module.exports = {
  namespace: "home-automation",
  nodeID: null,
  
  metadata: {},
  
  logger: {
    type: "Console",
    options: {
      colors: true,
      moduleColors: false,
      formatter: "full",
      objectPrinter: null,
      autoPadding: false
    }
  },
  
  logLevel: "info",
  
  transporter: process.env.NATS_URL || "nats://localhost:4222",
  
  cacher: {
    type: "Memory",
    options: {
      maxKeys: 1000,
      ttl: 30 * 60 // 30 minutes
    }
  },
  
  serializer: "JSON",
  
  requestTimeout: 10 * 1000,
  
  retryPolicy: {
    enabled: false,
    retries: 5,
    delay: 100,
    maxDelay: 1000,
    factor: 2,
    check: err => err && !!err.retryable
  },
  
  maxCallLevel: 100,
  
  heartbeatInterval: 10,
  heartbeatTimeout: 30,
  
  contextParamsCloning: false,
  
  tracking: {
    enabled: false,
    shutdownTimeout: 5000,
  },
  
  disableBalancer: false,
  
  registry: {
    strategy: "RoundRobin",
    preferLocal: true
  },
  
  circuitBreaker: {
    enabled: false,
    threshold: 0.5,
    minRequestCount: 20,
    windowTime: 60,
    halfOpenTime: 10 * 1000,
    check: err => err && err.code >= 500
  },
  
  bulkhead: {
    enabled: false,
    concurrency: 10,
    maxQueueSize: 100,
  },
  
  validator: true,
  
  errorHandler: null,
  
  created(broker) {},
  
  started(broker) {},
  
  stopped(broker) {}
};
