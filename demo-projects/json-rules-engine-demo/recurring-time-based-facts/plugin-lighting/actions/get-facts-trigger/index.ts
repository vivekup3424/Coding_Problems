import type { Context } from "moleculer";
import type { IGetFactsTriggerAction } from "../../../types";
import { FACTS_AND_TRIGGERS } from "../../constants";

export class GetFactsTriggerAction{
    static async handler(ctx:Context): Promise<IGetFactsTriggerAction.Response>{
        return {
            success: true,
            data: FACTS_AND_TRIGGERS,
        }
    }
}