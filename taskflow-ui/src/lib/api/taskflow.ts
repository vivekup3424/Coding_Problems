import { API_BASE_URL } from './config';
import type { ITaskflow, Taskflow } from '$lib/types/taskflow';
import axios from 'axios';
import { HttpHandler } from '$lib/utils/http-handler';
import type { TaskflowApiRequest } from './interfaces';


export class TaskflowApiCaller{

   static async getAllTaskflows(): Promise<Taskflow[]> {
    try {
      const response = await HttpHandler.PostCaller("GetAllTaskflows")
    
      if (!response?.data?.success) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return response?.data?.data;
    } catch (error) {
      console.error('Failed to fetch taskflows:', error);
      throw error;
    }
  }
  
   static async getTaskflowById(taskflowId: string): Promise<Taskflow> {
    try {
      const response = await HttpHandler.PostCaller("GetTaskflowDetails",{taskflowId});
      
      if (!response?.data?.success) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return response?.data?.data
    } catch (error) {
      console.error(`Failed to fetch taskflow ${taskflowId}:`, error);
      throw error;
    }
  }
  
   static async executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow): Promise<Taskflow> {
    try {
      const response = await HttpHandler.PostCaller("Produce",taskflow);
      
      if (!response?.data?.success) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return response?.data?.data;
    } catch (error) {
      console.error('Failed to execute taskflow:', error);
      throw error;
    }
  }
}