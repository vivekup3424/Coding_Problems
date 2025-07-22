import type Moleculer from "moleculer";
export namespace IAddNotificationToInboxAction {
    export interface Request {
        notification: Notification;
        inboxId: string;
    }
    export interface Response {
        success: boolean;
        error?: string;
        data?: string;  
    }   
}

class AddNotificationToInboxAction{
    static async handler(ctx: Moleculer.Context<>)
}