import type { TemplateContext } from "../../models/template";
import type { ITemplateRepository } from "../../domain/repositories/ITemplateRepository";
import { TemplateEntity } from "../../domain/entities/TemplateEntity";

/**
 * Application service for template management using clean architecture
 */
export class TemplateApplicationService {
  constructor(private templateRepository: ITemplateRepository) {}
  
  /**
   * Create a new template
   */
  async createTemplate(data: {
    name: string;
    content: string;
    parameters?: string[];
  }): Promise<TemplateEntity> {
    // Create new template entity
    const template = new TemplateEntity({
      name: data.name,
      content: data.content,
      parameters: data.parameters
    });
    
    // Save to repository
    await this.templateRepository.save(template);
    return template;
  }
  
  /**
   * Update an existing template
   */
  async updateTemplate(id: string, data: Partial<{
    name: string;
    content: string;
    parameters: string[];
  }>): Promise<TemplateEntity | null> {
    // Find existing template
    const template = await this.templateRepository.findById(id);
    if (!template) return null;
    
    // Update properties
    if (data.name) template.updateName(data.name);
    if (data.content && data.parameters) {
      template.updateContent(data.content, data.parameters);
    } else if (data.content) {
      template.updateContent(data.content);
    }
    
    // Save changes
    await this.templateRepository.update(template);
    return template;
  }
  
  /**
   * Render a template with the given context
   */
  async renderTemplate(id: string, context: TemplateContext): Promise<string> {
    const template = await this.templateRepository.findById(id);
    if (!template) {
      throw new Error(`Template with ID ${id} not found`);
    }
    
    return template.render(context);
  }
  
  /**
   * Get a template by ID
   */
  async getTemplate(id: string): Promise<TemplateEntity | null> {
    return this.templateRepository.findById(id);
  }
  
  /**
   * List all templates
   */
  async listTemplates(): Promise<TemplateEntity[]> {
    return this.templateRepository.list();
  }
  
  /**
   * Delete a template
   */
  async deleteTemplate(id: string): Promise<boolean> {
    return this.templateRepository.remove(id);
  }
}
