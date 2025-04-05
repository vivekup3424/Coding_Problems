import pino from "pino";
import { AsyncLocalStorage } from 'async_hooks'

export interface ILooseObject {
	[key: string]: any
}

type IndexedKeysType = {
	key1?: string | number;
	key2?: string | number;
	key3?: string | number;
	key4?: string | number;
	key5?: string | number;
	key6?: string | number;
	key7?: string | number;
	key8?: string | number;
	key9?: string | number;
	// .. more indexed keys to be added as and when needed.
};

type LogInput = {
	msg: string;
	data?: string | ILooseObject | boolean | number;
	success?: boolean;
	indexedKeys?: IndexedKeysType;
} | string;

interface IContext {
	env?: string
	appName?: string
	appVersion?: string
	// Indexer for optional properties
	[key: string]: any;
}

interface ILoggerSettings {
	prettyLogs?: boolean
	skipLogContext?: boolean
	context?: ILooseObject
}

export const contextStore = new AsyncLocalStorage<IContext>();

class _Logger {
	private pino
	private settings

	constructor({ prettyLogs = false, skipLogContext = false, context = {} }: ILoggerSettings = {}) {
		this.settings = { prettyLogs, skipLogContext, context }
		let pinoSettings: pino.LoggerOptions = {
			level: "trace",
			timestamp: pino.stdTimeFunctions.isoTime,
		}
		if (process.env.PRETTY_LOGS == "true") {
			pinoSettings = {
				...pinoSettings, transport: {
					target: 'pino-pretty',
					options: {
						colorize: true,
						colorizeObjects: true,
						singleLine: true,
						sync: true,
						// ignore: 'pid,hostname'
					}
				}
			}
		}
		this.pino = pino(pinoSettings)
		// this.debug({ msg: "Logger initialized", data: { ...pinoSettings } })
	}

	private enrichLog(args: LogInput) {

		args = typeof args === "string" ? { msg: args } : args

		if (process.env.SKIP_LOG_CONTEXT == "true") {
			return args;
		}

		return { ...args, ...contextStore.getStore(), ...this.settings.context }
	}

	error(args: LogInput) {
		this.pino.error(this.enrichLog(args));
	}

	warn(args: LogInput) {
		this.pino.warn(this.enrichLog(args));
	}

	info(args: LogInput) {
		this.pino.info(this.enrichLog(args));
	}

	debug(args: LogInput) {
		this.pino.debug(this.enrichLog(args));
	}
}

export type ILoggerInstance = {
	error(args: LogInput): void;
	warn(args: LogInput): void;
	info(args: LogInput): void;
	debug(args: LogInput): void;
};

export type ILogger = {
	getInstance(instanceContext?: ILooseObject): ILoggerInstance;
};

export class Logger {
	// private static instance: _Logger;

	private constructor() { }

	public static getInstance(instanceContext: ILooseObject = {}): ILoggerInstance {
		// if (!Logger.instance) {
		//     Logger.instance = new _Logger();
		// }
		// return Logger.instance;
		return new _Logger({ context: instanceContext });
	}
}
