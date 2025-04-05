import type { Context, ServiceBroker, ServiceSchema } from "moleculer";
import type { IResponse } from "../../../types";
import { AddFacts, AddTriggers } from "../../models/kiotp_facts_triggers_discovery";

export interface IFactsAndTriggers {
    TRIGGERS: {
        displayName: string;
        eventName: string;
        executionStrategy: string;
        params: any[];
    }[],
    FACTS: {
        factName: string;
        factValues: string[];
    }[]
}

export const fetchAllServices = async (broker: ServiceBroker): Promise<ServiceSchema[] | undefined> => {
    try {
        console.info("[RulesEngine] Fetching all services...");
        await broker.waitForServices("$node");
        const allServices = await broker.call("$node.services") as ServiceSchema[];
        console.info("[RulesEngine] Services fetched successfully", JSON.stringify(allServices, null, 2));
        return allServices;
    } catch (error) {
        console.error("[RulesEngine] Error during service fetch:", error);
    }
}

const addFactsAndTriggers = async (service: ServiceSchema, FACTS_AND_TRIGGERS: IFactsAndTriggers) => {
    try {
        console.info(`[RulesEngine] Processing facts and triggers for service: ${service.fullName}`);
        
        if (FACTS_AND_TRIGGERS.TRIGGERS) {
            FACTS_AND_TRIGGERS.TRIGGERS.forEach((trigger) => {
                console.info(`[RulesEngine] Adding Trigger: ${trigger.eventName}`);
                AddTriggers(
                    service.name,
                    service.version?.toString() || "",
                    trigger.eventName,
                    trigger.executionStrategy,
                    trigger.params
                );
            });
        }
        if (FACTS_AND_TRIGGERS.FACTS) {
            FACTS_AND_TRIGGERS.FACTS.forEach((fact) => {
                console.info(`[RulesEngine] Adding Fact: ${fact.factName}`);
                AddFacts(
                    service.name,
                    service.version?.toString() || "",
                    fact.factName,
                    fact.factValues
                );
            });
        }
    } catch (error) {
        console.error(`[RulesEngine] Error while adding facts and triggers for service: ${service.fullName}`, error);
    }
}

export const getNewService = async (broker: ServiceBroker): Promise<void> => {
    const existingServices = new Set<string>();

    try {
        console.info("[RulesEngine] Waiting for $node services...");
        await broker.waitForServices("$node");
        console.info("[RulesEngine] Fetching new services...");

        const allServices = await fetchAllServices(broker);
        if (!allServices) {
            console.warn("[RulesEngine] No services found");
            return;
        }

        const transformedServices = allServices.map(service => ({
            name: service.name,
            version: service.version,
            fullName: service.fullName,
        }));

        for (const service of transformedServices) {
            if (existingServices.has(service.fullName)) {
                console.info(`[RulesEngine] Service already processed: ${service.fullName}`);
                continue;
            }
            existingServices.add(service.fullName);
            const actionString = `${service.version}.${service.name}.GetFactsTrigger`;
            const action = broker.registry.actions.get(actionString);
            if (!action) {
                console.warn(`[RulesEngine] Action not found: ${actionString}`);
                continue;
            }
            console.info(`[RulesEngine] Calling action: ${actionString}`);
            const resp: IResponse = await broker.call(actionString);
            if (resp?.success) {
                console.info(`[RulesEngine] Successfully fetched facts and triggers for ${service.fullName}`);
                const FACTS_AND_TRIGGERS = resp.data as IFactsAndTriggers;
                console.debug("[RulesEngine] FACTS_AND_TRIGGERS", JSON.stringify(FACTS_AND_TRIGGERS, null, 2));
                await addFactsAndTriggers(service, FACTS_AND_TRIGGERS);
            } else {
                console.warn(`[RulesEngine] Failed to fetch facts and triggers for ${service.fullName}`);
            }
        }
    } catch (error) {
        console.error("[RulesEngine] Error during service processing:", error);
    }
}
