import { Engine} from "json-rules-engine";
import { RuleRegistry } from "./helpers/rules-engine-helper";
import type Moleculer from "moleculer";

class _RulesEngine {
  engine: Engine;

  constructor() {
    this.engine = new Engine();
  }

  execute(ctx:Moleculer.Context) {
    //@ts-ignore 
    let dependentRulesonFacts = RuleRegistry.getDependentRulesOfFacts(ctx.params.facts)

    RuleRegistry.addRulesAndUpdateFactsState(this.engine,dependentRulesonFacts)
    console.log("Running the engine, everything ok till here")
    return this.engine.run();
  }
}

export { _RulesEngine };
