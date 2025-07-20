import type { Logger } from "@infrastructure/logging";
import type { Notification } from "@domain/entities/notification";
export namespace ISendNotificationUsecase{
    export interface Response {
        success : boolean;
        data?: string;
        error?: string;
    }
}
export class SendNotificationUsecase{
    private logger: Logger;
    constructor(logger: Logger){
        this.logger = logger;
    }
    execute(notification: Notification): Promise<ISendNotificationUsecase.Response> {
        this.logger.info(JSON.stringify(notification));
        return Promise.resolve({
            success: true,
            data: `Notification of type ${notification.type} sent successfully`
        });
    }
}