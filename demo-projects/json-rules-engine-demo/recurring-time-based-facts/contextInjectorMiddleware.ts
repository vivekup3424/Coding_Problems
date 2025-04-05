import { ServiceBroker } from "moleculer";
export const contextInjectorMiddleware = () => {
  return {
    name: "ContextInjectorMiddleware",

    created(broker: ServiceBroker) {
      const originalSendToStream = broker.sendToChannel;

      if (!originalSendToStream) {
        broker.logger.warn(
          "[ContextInjector]: sendToChannel method not found on broker. Make sure this middleware is registered before the channels middleware."
        );
        return;
      }

      broker.sendToChannel = function (
        event: string,
        params: Record<string, any> = {},
        options: Record<string, any> = {}
      ) {
        try {
        if (!options) {
          options = {};
        }
          if(options.meta){
          options.meta = options.meta;
        }
          console.log("[ContextInjector] options.ctx", options);
        } catch (error) {
          broker.logger.warn(
            `[ContextInjector] Failed to create context: ${error}`
          );
        }

        return originalSendToStream.call(this, event, params, options);
      };
    },
  };
};
