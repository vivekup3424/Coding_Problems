import type { Template } from "../../models/template";
import { TemplateEntity } from "../entities/TemplateEntity";

/**
 * Repository interface for Template domain entity
 */
export interface ITemplateRepository {
  /**
   * Save a template entity
   */
  save(template: TemplateEntity): Promise<void>;
  
  /**
   * Find a template by ID
   */
  findById(id: string): Promise<TemplateEntity | null>;
  
  /**
   * Find all templates by name pattern
   */
  findByName(namePattern: string): Promise<TemplateEntity[]>;
  
  /**
   * Update a template entity
   */
  update(template: TemplateEntity): Promise<void>;
  
  /**
   * Remove a template by ID
   */
  remove(id: string): Promise<boolean>;
  
  /**
   * List all templates
   */
  list(): Promise<TemplateEntity[]>;
}
