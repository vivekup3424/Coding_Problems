import {Context} from "moleculer";
export namespace Authorization {
    export interface Request{
        userId: string;
        action: string;
        subject: string;
    }
    export interface Response{
        allowed: boolean;
    }
}
class Authorization{
    async can(ctx: Context<Authorization.Request>): Promise<Authorization.Response> {
        const { userId, action, subject } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.can",{userId, action, subject});
    }
    async getUserPermissions(ctx: Context<{ userId: string }>): Promise<any[]> {
        const { userId } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.getUserPermissions", { userId });
    }
    async getUserAccessibleRooms(ctx: Context<{ userId: string }>): Promise<any[]>  {
        const { userId } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.getUserAccessibleRooms", { userId });
    }
    async getUserAccessibleDevices(ctx: Context<{ userId: string }>): Promise<any[]> {
        const { userId } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.getUserAccessibleDevices", { userId });
    }
    async getUserAccessibleScenes(ctx: Context<{ userId: string }>): Promise<any[]> {
        const { userId } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.getUserAccessibleScenes", { userId });
    }
    async getUserAccessibleSchedules(ctx: Context<{ userId: string }>): Promise<any[]> {
        const { userId } = ctx.params;
        return await ctx.broker.call("1.0.0.local-authorization.getUserAccessibleSchedules", { userId });
    }   
}