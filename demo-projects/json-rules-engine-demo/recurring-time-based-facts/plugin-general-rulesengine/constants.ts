export const HubConstant = "MAIN_HUB_IP"

export enum CONSTANTS{
    SCENE = "SCENE",
    GROUP = "GROUP",
    ACTION = "ACTION",
    STATE = "STATE"
}

export namespace ActionType{

    export namespace Sleep{
        export const type = "SLEEP"

        export const delay = async (t:number) => new Promise((res)=>{
            setTimeout(() => {
                res(t);
            }, t*1000);
        });
        
    }

    export namespace State{
        export const type = CONSTANTS.STATE
    }

    export namespace Execute{
        
        export namespace Scene{
            export const type = CONSTANTS.SCENE
        }

        export namespace Group{
            export const type = CONSTANTS.GROUP;
        }

        export namespace Action{
            export const type = CONSTANTS.ACTION
        }
    }
}

export enum EventStrategy{
    FIRE_AND_FORGET = "fireandforget",
    DURABLE = "durable"
}

export namespace ConditionType{
    export const state = CONSTANTS.STATE
    export const action = CONSTANTS.ACTION
    export const scene = CONSTANTS.SCENE
    export const group = CONSTANTS.GROUP
}