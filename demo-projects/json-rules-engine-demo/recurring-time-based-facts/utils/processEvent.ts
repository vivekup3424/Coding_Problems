import type { ServiceBroker } from "moleculer";
import { v4 } from "uuid";
import { AsyncDelay } from "../types";
import type Moleculer from "moleculer";

interface Document {
  // Assuming Document interface definition
}

interface IExecution extends Document {
  serviceId: string;
  executionName: string;
  executionStrategy?: string;
  action?: string;
  moleculerEvent?: string;
  customExecutionData?: object;
}

interface IEventExecution {
  serviceId: string;
  executionName: string;
  executionStrategy: string;
  moleculerEvent: string;
  customExecutionData: object;
}

interface IChannelExecution {
  serviceId: string;
  executionName: string;
  executionStrategy: string;
  moleculerEvent: string;
  customExecutionData: object;
}

interface IActionExecution {
  serviceId: string;
  executionName: string;
  action: string;
  customExecutionData: object;
}

// Type guard functions to check if an IExecution can be treated as a specific type
function isChannelExecution(execution: IExecution): execution is IChannelExecution {
  return execution.executionStrategy === "durable" && 
         typeof execution.moleculerEvent === "string" && 
         typeof execution.customExecutionData === "object";
}

function isEventExecution(execution: IExecution): execution is IEventExecution {
  return execution.executionStrategy === "fireNforget" && 
         typeof execution.moleculerEvent === "string" && 
         typeof execution.customExecutionData === "object";
}

function isActionExecution(execution: IExecution): execution is IActionExecution {
  return typeof execution.action === "string" && 
         typeof execution.customExecutionData === "object";
}

const processChannel = (broker: ServiceBroker, execution: IChannelExecution, metadata: Record<any, any>) => {
  broker.logger.info("[RulesEngine] Sending durable event:", execution.moleculerEvent);
  return broker.sendToChannel(execution.moleculerEvent, execution.customExecutionData, {
    meta: {
      [v4()]: execution.serviceId,
      ...metadata
    }
  });
};

const processEvent = (broker: ServiceBroker, execution: IEventExecution, metadata: Record<any, any>) => {
  broker.logger.info("[RulesEngine] Sending fireNforget event:", execution.moleculerEvent);
  return broker.emit(execution.moleculerEvent, execution.customExecutionData, {
    meta: {
      [v4()]: execution.serviceId,
      ...metadata
    }
  });
};

const processAction = (broker: ServiceBroker, execution: IActionExecution, metadata: Record<any, any>) => {
  const actionPath = `${execution.serviceId}.${execution.action}`;
  broker.logger.info("[RulesEngine] Executing action:", actionPath);
  return broker.call(actionPath, execution.customExecutionData, {
    meta: {
      [v4()]: execution.serviceId,
      ...metadata
    }
  });
};

export const processDelay = async (broker: ServiceBroker, delay: number) => {
  broker.logger.warn("[RulesEngine] Delaying next routine by ", delay, " seconds");
  await AsyncDelay(delay*1000)
};

export const executeRoutines = (broker: ServiceBroker, executions: IExecution[], metadata: Record<any, any>) => {
  const executionPromises: Array<Promise<any>> = [];
  
  for (const execution of executions) {
    if (isChannelExecution(execution)) {
      executionPromises.push(processChannel(broker, execution, metadata));
    } else if (isEventExecution(execution)) {
      executionPromises.push(processEvent(broker, execution, metadata));
    } else if (isActionExecution(execution)) {
      executionPromises.push(processAction(broker, execution, metadata));
    } else {
      broker.logger.warn("[RulesEngine] Execution doesn't match any supported type:", execution);
    }
  }
  
  return Promise.all(executionPromises);
};

export const isFactModifiedByAnotherRule = (broker: ServiceBroker,ctx: Moleculer.Context)=> {
  if(ctx.meta && "engine" in ctx.meta){
    broker.logger.warn("[RulesEngine] Nested Rule detected")
    return true;
  }
  return false;
}
export const addEngineMetaIntoContext=(ctx: Moleculer.Context)=>{
  ctx.meta = {...ctx.meta,engine:1};
  return ctx
}