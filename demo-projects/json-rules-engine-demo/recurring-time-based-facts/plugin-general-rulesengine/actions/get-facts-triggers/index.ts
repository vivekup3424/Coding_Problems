import { Context } from "moleculer";
import type { IGetFactsTriggerAction } from "../../../types";
class GetFactsTriggerAction {
    static params = {
    }

    static hooks = {
        before(ctx: Context) {
            console.log('this is before', ctx.params);
        },
        after(ctx: Context, res: IGetFactsTriggerAction.Response) {
            console.log('this is after ', ctx.params, res);

            return res;
        },
    }

    static async handler(ctx: Context): Promise<IGetFactsTriggerAction.Response> {
        console.log(ctx.params, ctx.id);
        let response:any =  await ctx.broker.call(`$node.services`);
        let pluginsList: Array<any>  = response.pluginsInfo
        let facts = []
        let factsAndtriggers : any = {}
        //@ts-ignore
        if (pluginsList.length > 0) {
            //@ts-ignore
            for (let i = 0; i < pluginsList.length; i++) {
                //@ts-ignore
                try {
                    //@ts-ignore
                    let pluginDetails = pluginsList[i].pluginInfo
                    let id = pluginDetails.id
                    let version = pluginDetails.version
                    let triggerAndFacts: any = await ctx.broker.call(`${version}.${id}.GetTriggersAndFacts`, {})
                    if (triggerAndFacts.success && triggerAndFacts.data !=null) {
                        factsAndtriggers[id] = triggerAndFacts.data

                    }
                } catch (err) {
                    console.log("error", err)
                }
            }
        }

        try {
        } catch (err) {
            console.log('error', err);
        }

        return {
            success: true,
            data: factsAndtriggers
        };
    }
}

export { GetFactsTriggerAction };