import { writable, derived } from 'svelte/store';
import type { ITemplate, Template } from '$lib/types/template';
import { taskflowsMap } from './taskflow';
import { TemplateApiCaller } from '$lib/api/template';
import { TaskflowApi } from '$lib/api/taskflow-api';

export const templatesMap = writable<Map<string, Template>>(new Map());

export const templates = derived(templatesMap, $map => Array.from($map.values()));

export const selectedTemplate = writable<Template | null>(null);
export const showTemplatePopup = writable<boolean>(false);

export const templateActions = {
  async fetchTemplates() {
    try {
      const data = await TaskflowApi.getAllTemplates();
      
      const newMap = new Map<string, Template>();
      data.forEach(template => {
        newMap.set(template.templateId, template);
      });
      
      templatesMap.set(newMap);
      return { success: true };
    } catch (error) {
      console.error('Failed to fetch templates:', error);
      return { success: false, error };
    }
  },
  
  async createTemplate(templateData: ITemplate) {
    try {
      const newTemplate = await TaskflowApi.createTemplate(templateData);
      
      templatesMap.update(map => {
        const newMap = new Map(map);
        if (newTemplate && newTemplate.templateId) {
          newMap.set(newTemplate.templateId, newTemplate);
        }
        return newMap;
      });
      
      return { success: true, template: newTemplate };
    } catch (error) {
      console.error('Failed to create template:', error);
      return { success: false, error };
    }
  },
  
  async updateTemplate(templateData: Partial<Template>) {
    try {
      // Assuming the API exists to update templates
      // Replace with actual API call once available
      const updatedTemplate = await TaskflowApi.updateTemplate(templateData);
      
      templatesMap.update(map => {
        const newMap = new Map(map);
        if (updatedTemplate && updatedTemplate.templateId) {
          newMap.set(updatedTemplate.templateId, updatedTemplate);
        }
        return newMap;
      });
      
      return { success: true, template: updatedTemplate };
    } catch (error) {
      console.error('Failed to update template:', error);
      return { success: false, error };
    }
  },
  
  async deleteTemplate(templateId: string) {
    try {
      // Assuming the API exists to delete templates
      // Replace with actual API call once available
      await TaskflowApi.deleteTemplate(templateId);
      
      templatesMap.update(map => {
        const newMap = new Map(map);
        newMap.delete(templateId);
        return newMap;
      });
      
      return { success: true };
    } catch (error) {
      console.error('Failed to delete template:', error);
      return { success: false, error };
    }
  },
  
  async executeTemplate(templateId: string) {
    try {
      const taskflow = await TaskflowApi.executeTemplate(templateId);
      
      taskflowsMap.update(map => {
        const newMap = new Map(map);
        if (taskflow && taskflow.taskflowId) {
          newMap.set(taskflow.taskflowId, taskflow);
        }
        return newMap;
      });
      
      return { success: true, taskflow };
    } catch (error) {
      console.error('Failed to execute template:', error);
      return { success: false, error };
    }
  },
  
  showTemplateDetails(template: Template) {
    selectedTemplate.set(template);
    showTemplatePopup.set(true);
  },
  
  closeTemplatePopup() {
    showTemplatePopup.set(false);
    selectedTemplate.set(null);
  }
};