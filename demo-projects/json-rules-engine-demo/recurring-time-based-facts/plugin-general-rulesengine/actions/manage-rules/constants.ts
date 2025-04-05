export namespace RuleConditionOperations{
    export namespace Equal{
        export const type = "equal"
    }

    export namespace GreaterThan{
        export const type = "greaterThan"
    }

    export namespace GreaterThanInclusive{
        export const type = "greaterThanInclusive"
    }

    export namespace LessThan{
        export const type = "lessThan"
    }

    export namespace LessThanInclusive{
        export const type = "lessThanInclusive"
    }

    export function GetOperations():string[]{
        return [Equal.type, LessThan.type, GreaterThan.type, GreaterThanInclusive.type, LessThanInclusive.type]
    }

    export function validOperation(operation:string):boolean{
        switch(operation){
            case RuleConditionOperations.Equal.type:
            case RuleConditionOperations.GreaterThan.type:
            case RuleConditionOperations.LessThan.type:
            case RuleConditionOperations.GreaterThanInclusive.type:
            case RuleConditionOperations.LessThanInclusive.type:
                return true;
            default:
                return false;
        }
    }
}
