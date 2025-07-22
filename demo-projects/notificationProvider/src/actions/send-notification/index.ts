import {NotificationType, type Notification} from "../../models/data/notification";
import Moleculer from "moleculer";
import { logger } from "../../logger";
export namespace ISendNotificationAction {
  export interface Request {
    notification: Notification;
  }

  export interface Response {
    success: boolean;
    error?: string;
    data?: string;
  }
}

class SendNotificationAction {
  static params = {};

  static hooks = {
    before(ctx: Moleculer.Context<ISendNotificationAction.Request>) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Moleculer.Context<ISendNotificationAction.Request>, res: ISendNotificationAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

static async handler(ctx: Moleculer.Context<ISendNotificationAction.Request>): Promise<ISendNotificationAction.Response> {
    try {

      if(!ctx.params.notification){
        throw new Error("notification is required")
      }
      logger.info(JSON.stringify(ctx.params.notification));


      switch (ctx.params.notification.type) {
        case NotificationType.EMAIL:
            logger.info("Sending email notification");
            break;
        case NotificationType.WHATSAPP:
            logger.info("Sending WhatsApp notification");
            break;
        case NotificationType.SMS:
            logger.info("Sending SMS notification");
            break;
        case NotificationType.PUSH:
            logger.info("Sending Push notification");
            break;
        default:
            break;
      }
      return {
        success: true,
        data: `Notification of type ${ctx.params.notification.type} sent successfully.`
      }
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { SendNotificationAction };

