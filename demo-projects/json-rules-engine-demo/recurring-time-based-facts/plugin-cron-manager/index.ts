import cron from 'node-cron';
import type { ScheduledTask } from 'node-cron';
import { ServiceBroker, Service, Context } from 'moleculer';
//whenver you are adding a job, you also need to add when this job should end
interface JobInfo {
  id: string,
  task: ScheduledTask;
  cronExpression: string;
  taskFunction: () => void;
  //   duration: number; // in minutes
  //   complementId: string; // ID of the job which will end this job
}

export class CronManager extends Service {
  private jobs: Record<string, JobInfo>;

  constructor(broker: ServiceBroker) {
    super(broker);
    this.jobs = {};
    this.parseServiceSchema({
      version:"1.0.0",
      name: "cron.manager",
      actions: {
        addJob: this.addJob,
        removeJob: this.removeJob,
        rescheduleJob: this.rescheduleJob,
        listJobs: this.listJobs,
      }
    })
  }

  /**
   * Adds a new cron job.
   * @param id - Unique ID for the job.
   * @param cronExpression - Cron expression for the job.
   * @param taskFunction - Function to execute at scheduled times.
   * @returns `true` if the job was added, `false` if the ID already exists.
   * @throws Error if the cron expression is invalid
   */
  addJob(ctx: Context): boolean {
    const {id,cronExpression,taskFunction} = <JobInfo>ctx.params;
    if (this.jobs[id]) {
      console.log(`Job with ID ${id} already exists.`);
      return false;
    }

    if (!cron.validate(cronExpression)) {
      console.error(cronExpression)
      throw new Error(`Invalid cron expression: ${cronExpression}`);
    }

    try {
      const task = cron.schedule(cronExpression, taskFunction);
      console.trace("addJob called");
      this.jobs[id] = {
        id,
        task,
        cronExpression,
        taskFunction
      };
      console.log(`Job ${id} added with schedule: ${cronExpression}`);
      return true;
    } catch (error) {
      console.error(`Error scheduling job ${id}:`, error);
      throw error;
    }
  }
  // addJob(ctx: Context): boolean {
  //   const { id, taskFunction } = <JobInfo>ctx.params;

  //   if (this.jobs[id]) {
  //     console.log(`Job with ID ${id} already exists.`);
  //     return false;
  //   }

  //   try {
  //     // Run task every 1 minute (60,000 ms)
  //     const task = setInterval(() => {
  //       console.log(`Executing job ${id} at`, new Date().toISOString());
  //       taskFunction();
  //     }, 60000);
  //     console.log(`Job ${id} added to run every 1 minute.`);
  //     return true;
  //   } catch (error) {
  //     console.error(`Error scheduling job ${id}:`, error);
  //     throw error;
  //   }
  // }

  /**
   * Removes an existing cron job.
   * @param id - Unique ID of the job to remove.
   * @returns `true` if the job was removed, `false` if the ID does not exist.
   */
  removeJob(id: string): boolean {
    const jobInfo = this.jobs[id];
    if (!jobInfo) {
      console.log(`Job with ID ${id} does not exist.`);
      return false;
    }

    jobInfo.task.stop();
    delete this.jobs[id];
    console.log(`Job ${id} removed.`);
    return true;
  }

  /**
   * Reschedules an existing cron job with a new cron expression.
   * @param id - Unique ID of the job to reschedule.
   * @param newCronExpression - New cron expression for the job.
   * @returns `true` if the job was rescheduled, `false` if the ID does not exist.
   * @throws Error if the new cron expression is invalid
   */
  rescheduleJob(id: string, newCronExpression: string): boolean {
    const jobInfo = this.jobs[id];
    if (!jobInfo) {
      console.log(`Job with ID ${id} does not exist.`);
      return false;
    }

    if (!cron.validate(newCronExpression)) {
      throw new Error(`Invalid cron expression: ${newCronExpression}`);
    }

    try {
      jobInfo.task.stop();
      const newTask = cron.schedule(newCronExpression, jobInfo.taskFunction);
      this.jobs[id] = {
        id,
        task: newTask,
        cronExpression: newCronExpression,
        taskFunction: jobInfo.taskFunction
      };
      console.log(`Job ${id} rescheduled with new schedule: ${newCronExpression}`);
      return true;
    } catch (error) {
      console.error(`Error rescheduling job ${id}:`, error);
      throw error;
    }
  }

  /**
   * Lists all currently active jobs.
   */
  listJobs(): void {
    console.log("Active Jobs:");
    for (const [id, jobInfo] of Object.entries(this.jobs)) {
      console.log(`- Job ID: ${id}, Schedule: ${jobInfo.cronExpression}`);
    }
  }
}

export default CronManager;