import type { ITemplate, Template } from '$lib/types/template';
export declare const templatesMap: import("svelte/store").Writable<Map<string, Template>>;
export declare const templates: import("svelte/store").Readable<Template[]>;
export declare const selectedTemplate: import("svelte/store").Writable<any>;
export declare const showTemplatePopup: import("svelte/store").Writable<boolean>;
export declare const templateActions: {
    fetchTemplates(): Promise<{
        success: boolean;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
    }>;
    createTemplate(templateData: ITemplate): Promise<{
        success: boolean;
        template: any;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
        template?: undefined;
    }>;
    updateTemplate(templateData: Partial<Template>): Promise<{
        success: boolean;
        template: any;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
        template?: undefined;
    }>;
    deleteTemplate(templateId: string): Promise<{
        success: boolean;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
    }>;
    executeTemplate(templateId: string): Promise<{
        success: boolean;
        taskflow: any;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
        taskflow?: undefined;
    }>;
    showTemplateDetails(template: Template): void;
    closeTemplatePopup(): void;
};
