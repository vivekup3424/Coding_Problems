import { API_BASE_URL } from './config';
import type { ITemplate, Template } from '$lib/types/template';
import type { Taskflow } from '$lib/types/taskflow';
import axios from 'axios';
import { HttpHandler } from '$lib/utils/http-handler';

export class TemplateApiCaller{

   static async getAllTemplates(): Promise<Template[]> {
    try {
      const response = await HttpHandler.GetCaller("GetAllTemplates");
      // console.log("all templates reqponse---",response)
    const allTemplates = response?.data?.data
      if (!response?.data?.success) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return allTemplates;
    } catch (error) {
      console.error('Failed to fetch templates:', error);
      throw error;
    }
  }
  
   static async getTemplateById(id: string): Promise<Template> {
    try {
      const response = await HttpHandler.PostCaller(`${API_BASE_URL}/taskflow/GetTemplateById?id=${id}`);
      
      if (!response.ok) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return await response.json();
    } catch (error) {
      console.error(`Failed to fetch template ${id}:`, error);
      throw error;
    }
  }
  
   static async createTemplate(template: Omit<ITemplate, 'id' | 'createdAt'>): Promise<Template> {
    try {
      const data = {
        template
      }
      const response = await HttpHandler.PostCaller("AddTemplate",data)
      
      if (!response?.data?.success) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return response?.data?.data
    } catch (error) {
      console.error('Failed to create template:', error);
      throw error;
    }
  }
  
   static async executeTemplate(templateId: string): Promise<Taskflow> {
    try {
      
      const response = await HttpHandler.PostCaller("ExecuteTemplate", {templateId});
      // console.log(response)
      if (!response?.data?.success || ! response?.data?.data) {
        throw new Error(`API error: ${response.status}`);
      }
      
      return response?.data?.data
    } catch (error) {
      console.error('Failed to execute template:', error);
      throw error;
    }
  }
}
