import { Service, Errors } from "moleculer";

export class JobService extends Service {
    constructor(broker) {
        super(broker);

        this.parseServiceSchema({
            name: "jobService",
            actions: {
                startJob: {
                    params: {
                        taskId: "string",
                    },
                    async handler(ctx) {
                        const { jobId } = ctx.params;
                        this.logger.info(`Job ${jobId} Started`);
                        //wait for all the task to be finished
                        
                        this.broker.sendToChannel("p2.job.completed", { jobId });
                        this.logger.info(`Job ${jobId} Completed`);
                        return { success: true, jobId };
                    }
                },
            },
            channels: {
                "p2.job.completed": {
                    handler(ctx) {
                        this.logger.info(`Task ${ctx.params.taskId} is successfully completed.`);
                    }
                },
                "p2.task.running": {
                    handler(ctx) {
                        this.logger.info(`Task ${ctx.params.taskId} is running`);
                    }
                },
                "p2.task.queued": {
                    handler(ctx) {
                        this.logger.info(`Task ${ctx.params.taskId} queued successfully.`);
                    }
                },
                "p2.task.execution.failed": {
                    handler(ctx) {
                        this.logger.warn(`Task ${ctx.params.taskId} failed.`);
                    }
                },
                "p2.task.retrying":{
                    handler(ctx){
                        this.logger.warn(`Retrying to executed ${ctx.params.taskId}`)
                    }
                }
            }
        });
    }

    async runStages(jobId, stages) {
        const stageStatus = {};

        for (const stage of stages) {
            stageStatus[stage.id] = "Queued";
        }

        const executeStage = async (stage) => {
            // Ensure dependencies are completed
            for (const dep of stage.dependsOn) {
                if (stageStatus[dep] !== "Success") {
                    this.logger.info(`Stage ${stage.id} waiting for ${dep} to complete.`);
                    return setTimeout(() => executeStage(stage), 500);
                }
            }

            stageStatus[stage.id] = "Started";
            this.broker.emit("stage.started", { jobId, stageId: stage.id });
            this.logger.info(`Executing Stage: ${stage.id}`);

            try {
                stageStatus[stage.id] = "Running";
                await this.processStage(stage.id);
                stageStatus[stage.id] = "Success";

                this.broker.emit("stage.success", { jobId, stageId: stage.id });
                this.logger.info(`Stage ${stage.id} executed successfully`);
            } catch (err) {
                stageStatus[stage.id] = "Retrying";
                this.logger.warn(`Retrying Stage ${stage.id}: ${err.message}`);

                for (let retry = 0; retry < 3; retry++) {
                    try {
                        await this.processStage(stage.id);
                        stageStatus[stage.id] = "Success";
                        this.broker.emit("stage.success", { jobId, stageId: stage.id });
                        return;
                    } catch (retryErr) {
                        this.logger.warn(`Retry ${retry + 1} for Stage ${stage.id} failed`);
                    }
                }

                stageStatus[stage.id] = "Failed";
                this.broker.emit("stage.failed", { jobId, stageId: stage.id });
                this.logger.error(`Stage ${stage.id} permanently failed`);
            }
        };

        for (const stage of stages) {
            executeStage(stage);
        }
    }

    async processStage(stageId) {
        // Simulate processing time & failure
        await this.wait(Math.random() * 2000);

        if (Math.random() < 0.3) {
            throw new Errors.MoleculerRetryableError(`Stage ${stageId} encountered an error.`);
        }
    }

    wait(ms) {
        return new Promise((resolve) => setTimeout(resolve, ms));
    }
}
