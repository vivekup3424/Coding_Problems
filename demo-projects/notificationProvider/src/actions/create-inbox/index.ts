import type Moleculer from "moleculer";
import { Inbox } from "../../models/data/inbox";
export namespace ICreateInboxAction {
    export interface Request{
        notificationCleanupInterval: number;
    }
    export interface Response {
        success: boolean;
        error?: string;
        data?: string;  
    }
}

class CreateInboxAction {
    static async handler(ctx: Moleculer.Context<ICreateInboxAction.Request>): Promise<ICreateInboxAction.Response> {
        try {
            const { notificationCleanupInterval } = ctx.params;

            const id = crypto.randomUUID();
            const inbox = new Inbox({
                id,
                notificationCleanupInterval,
                notificationIds: []
            });
            // Save the inbox to the database
            await inbox.save();

            return {
                success: true,
                data: `Inbox created with ID: ${inbox.id}`
            };
        } catch (err) {
            return {
                success: false,
                error: err.message
            };
        }
    }
}