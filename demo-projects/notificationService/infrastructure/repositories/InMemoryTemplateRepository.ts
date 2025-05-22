import type { Template } from "../../models/template";
import type { ITemplateRepository } from "../../domain/repositories/ITemplateRepository";
import { TemplateEntity } from "../../domain/entities/TemplateEntity";

/**
 * In-memory implementation of the template repository
 */
export class InMemoryTemplateRepository implements ITemplateRepository {
  private templates = new Map<string, Record<string, any>>();
  
  async save(template: TemplateEntity): Promise<void> {
    const data = template.toJSON();
    this.templates.set(template.id, data);
  }
  
  async findById(id: string): Promise<TemplateEntity | null> {
    const data = this.templates.get(id);
    return data ? TemplateEntity.fromJSON(data) : null;
  }
  
  async findByName(namePattern: string): Promise<TemplateEntity[]> {
    const regex = new RegExp(namePattern, 'i');
    return Array.from(this.templates.values())
      .filter(data => regex.test(data.name))
      .map(data => TemplateEntity.fromJSON(data));
  }
  
  async update(template: TemplateEntity): Promise<void> {
    const data = template.toJSON();
    this.templates.set(template.id, data);
  }
  
  async remove(id: string): Promise<boolean> {
    return this.templates.delete(id);
  }
  
  async list(): Promise<TemplateEntity[]> {
    return Array.from(this.templates.values())
      .map(data => TemplateEntity.fromJSON(data));
  }
}
