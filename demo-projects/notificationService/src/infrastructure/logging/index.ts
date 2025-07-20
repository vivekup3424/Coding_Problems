import pino from "pino";

export class Logger{
    private logger: pino.Logger;
    constructor(){
        this.logger = pino({
            level: process.env.LOG_LEVEL || "info",
        }, pino.destination("./apps.log"));
    }
    public info(message: string) {
        this.logger.info(message);
    }
    public warn(message: string) {
        this.logger.warn(message);
    }
    public error(message: string) {
        this.logger.error(message);
    }
    public debug(message: string) {
        this.logger.debug(message);
    }
    public fatal(message: string) {
        this.logger.fatal(message);
    }
}