import pino from "pino";

// why to use singleton here??
const logger = pino({
    level: process.env.LOG_LEVEL || "info",
}, pino.destination("./apps.log")
)

logger.info("Logger initialized with level:", process.env.LOG_LEVEL || "info");
logger.error("This is an error message");
logger.warn("This is a warning message");