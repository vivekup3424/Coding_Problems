import Moleculer, { Service, ServiceBroker } from "moleculer";
import * as Actions from "./actions";
import { mongoInstance } from "./models/mongo-connector";
class PluginService extends Service {
  constructor(broker: ServiceBroker) {
    super(broker);

    this.parseServiceSchema({
      name: "taskflow",
      version: "1.0.0",
      meta: {
        scalable: false,
      },
      dependencies: [],
      settings: {
        upperCase: true,
      },
      actions: {
        Produce: Actions.TFProduceAction.handler,
        GetTaskflowDetails: Actions.GetTaskflowStateAction.handler,
        GetAllTaskflowsDetails: Actions.GetAllTaskflowsAction.handler,
        AddTemplate: Actions.AddTemplateAction.handler,
        ExecuteTemplate: Actions.ExecuteTemplateAction.handler,
        UpdateTemplate: Actions.UpdateTemplateAction.handler,
        DeleteTemplate: Actions.DeleteTemplateAction.handler,
        GetTemplate: Actions.GetTemplateAction.handler,
        GetAllTemplates: Actions.GetAllTemplatesAction.handler,
        CancelTaskflow: Actions.CancelTaskflowAction.handler,
        RetryTaskflow: {
          params:Actions.TFRetryTaskflowAction.params,
          handler: Actions.TFRetryTaskflowAction.handler,
          hooks: Actions.TFRetryTaskflowAction.hooks
          
        }
      },
      methods: {

      },
      events: {

      },
      channels: {
        "p1.channel.event.status": {
          group: `taskflow-channel-status`,
          handler: async (ctx: Moleculer.Context<ITaskflow.ChannelHandlerStatus, ITaskflow.TaskFlowContextMeta>) => {
            const taskflowDetails = ctx.meta?.taskflowExecutionContext?.taskflow

            if (!taskflowDetails || !taskflowDetails.taskInfo) {
              return
            }

            taskFlowManager.processTaskStatus(ctx)
          }
        },
        "default.deadLetter.queue": {
          group: `taskflow-dead-queue`,
          handler: async (ctx: Moleculer.Context<ITaskflow.ChannelHandlerStatus>) => {
            return true
          }
        },
        "p1.taskflow.process-taskflow": {
          group: `process-taskflow`,
          handler: async (ctx: Moleculer.Context<{ taskflowId: string }, ITaskflow.TaskFlowContextMeta>) => {

            const { taskflowId } = ctx.params;

            await taskFlowManager.processTaskflow(taskflowId, ctx);

            return true

          }
        },
        "p1.taskflow.task.execute": {
          group: "taskflow-task-execute",
          handler: ExecuteTaskChannelEvent.handler
        }
      },
      created: this.serviceCreated,
      started: this.serviceStarted,
      stopped: this.serviceStopped,
    });
  }

  async serviceCreated() {
    await mongoInstance.start()
  }

  async serviceStarted() {

  }

  serviceStopped() {

  }
}

export { PluginService };