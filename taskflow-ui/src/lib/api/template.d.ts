import type { ITemplate, Template } from '$lib/types/template';
import type { Taskflow } from '$lib/types/taskflow';
export declare class TemplateApiCaller {
    static getAllTemplates(): Promise<Template[]>;
    static getTemplateById(id: string): Promise<Template>;
    static createTemplate(template: Omit<ITemplate, 'id' | 'createdAt'>): Promise<Template>;
    static executeTemplate(templateId: string): Promise<Taskflow>;
}
