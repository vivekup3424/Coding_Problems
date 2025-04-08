const addFactsAndTasks = async (service: ServiceSchema, factsAndTasks: IFactsAndTasks): Promise<void> => {
	try {
		console.info(`[RulesEngine] Processing facts and tasks for service: ${service.fullName}`);
		const serviceId = (service.version || "") + service.name;
		if (factsAndTasks.TASKS && Array.isArray(factsAndTasks.TASKS)) {
			for (const task of factsAndTasks.TASKS) {
				console.info(`[RulesEngine] Adding Task: ${task.taskName}`);
				await factsAndTaskManager.addTask(
					serviceId,
					task.taskName,
					task.taskType,
					task.taskAction,
					task.possibleTaskValues || [],
					task.params || {}
				);
			}
		}

		if (factsAndTasks.FACTS && Array.isArray(factsAndTasks.FACTS)) {
			for (const fact of factsAndTasks.FACTS) {
				console.info(`[RulesEngine] Adding Fact: ${fact.factName}`);
				await factsAndTaskManager.addFact(
					serviceId,
					fact.factName,
					fact.factAction,
					fact.factValues,
					fact.params,
					fact.validOperations
				);
			}
		}
	} catch (error) {
		console.error(`[RulesEngine] Error while adding facts and tasks for service: ${service.fullName}`, error);
	}
};

/*Storing the interfaces here*/
interface IFactDefinition {
	factName: string;
	factAction: string;
	factValues: any[];
	factRelativePath?: string;
	params?: object;
	validOperations?: string[];
}

/**
 * Interface for task definition in service metadata
 */
interface ITaskDefinition {
	taskName: string;
	taskAction: string;
	taskType: TaskType;
	params?: any[];
	possibleTaskValues?: any[];
}
export enum TaskType {
	ACTION = "ACTION",
	CHANNEL_EVENT = "CHANNEL",
	EVENT = "EVENT"

}
