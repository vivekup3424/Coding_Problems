import type { ITemplateRepository } from "../../domain/repositories/ITemplateRepository";
import { TemplateEntity } from "../../domain/entities/TemplateEntity";
import { TemplateModel } from "../database/schemas/TemplateSchema";

/**
 * MongoDB implementation of the template repository
 */
export class MongoTemplateRepository implements ITemplateRepository {
  
  /**
   * Save a template entity to MongoDB
   */
  async save(template: TemplateEntity): Promise<void> {
    const data = template.toJSON();
    
    await TemplateModel.findOneAndUpdate(
      { id: template.id },
      data,
      { upsert: true, new: true }
    );
  }
  
  /**
   * Find a template by ID from MongoDB
   */
  async findById(id: string): Promise<TemplateEntity | null> {
    const template = await TemplateModel.findOne({ id }).lean();
    return template ? TemplateEntity.fromJSON(template) : null;
  }
  
  /**
   * Find templates by name pattern from MongoDB
   */
  async findByName(namePattern: string): Promise<TemplateEntity[]> {
    // Create a regex pattern for case-insensitive search
    const regexPattern = new RegExp(namePattern, 'i');
    
    const templates = await TemplateModel.find({ 
      name: { $regex: regexPattern } 
    }).lean();
    
    return templates.map(data => TemplateEntity.fromJSON(data));
  }
  
  /**
   * Update a template entity in MongoDB
   */
  async update(template: TemplateEntity): Promise<void> {
    const data = template.toJSON();
    
    await TemplateModel.updateOne(
      { id: template.id },
      { $set: data }
    );
  }
  
  /**
   * Remove a template by ID from MongoDB
   */
  async remove(id: string): Promise<boolean> {
    const result = await TemplateModel.deleteOne({ id });
    return result.deletedCount > 0;
  }
}
