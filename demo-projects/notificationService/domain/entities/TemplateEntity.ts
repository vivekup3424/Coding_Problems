import { v4 as uuidv4 } from "uuid";
import { TemplateRenderer } from "../../utils/TemplateRenderer";
import type { TemplateContext } from "../../models/template";

/**
 * Template entity representing a notification template in the domain
 */
export class TemplateEntity {
  readonly id: string;
  private _name: string;
  private _content: string;
  private _parameters: string[];
  readonly createdAt: Date;
  private _updatedAt: Date;

  constructor(props: {
    id?: string;
    name: string;
    content: string;
    parameters?: string[];
    createdAt?: Date;
    updatedAt?: Date;
  }) {
    this.id = props.id || uuidv4();
    this._name = props.name;
    this._content = props.content;
    
    // Extract parameters if not provided
    this._parameters = props.parameters || 
      TemplateRenderer.extractParameters(props.content);
    
    this.createdAt = props.createdAt || new Date();
    this._updatedAt = props.updatedAt || new Date();
  }

  /**
   * Get the template name
   */
  get name(): string {
    return this._name;
  }

  /**
   * Get the template content
   */
  get content(): string {
    return this._content;
  }

  /**
   * Get the parameters required by this template
   */
  get parameters(): string[] {
    return [...this._parameters];
  }

  /**
   * Get the last updated timestamp
   */
  get updatedAt(): Date {
    return this._updatedAt;
  }

  /**
   * Update the template name
   */
  updateName(name: string): void {
    this._name = name;
    this._updatedAt = new Date();
  }

  /**
   * Update the template content
   */
  updateContent(content: string, parameters?: string[]): void {
    this._content = content;
    
    // Extract parameters if not provided
    if (!parameters) {
      this._parameters = TemplateRenderer.extractParameters(content);
    } else {
      this._parameters = parameters;
    }
    
    this._updatedAt = new Date();
  }

  /**
   * Render the template with the provided context
   */
  render(context: TemplateContext): string {
    return TemplateRenderer.render({
      id: this.id,
      name: this._name,
      content: this._content,
      parameters: this._parameters,
      createdAt: this.createdAt,
      updatedAt: this._updatedAt
    }, context);
  }

  /**
   * Convert entity to a plain object for persistence
   */
  toJSON() {
    return {
      id: this.id,
      name: this._name,
      content: this._content,
      parameters: this._parameters,
      createdAt: this.createdAt,
      updatedAt: this._updatedAt
    };
  }

  /**
   * Create a TemplateEntity from a plain object
   */
  static fromJSON(data: any): TemplateEntity {
    return new TemplateEntity({
      id: data.id,
      name: data.name,
      content: data.content,
      parameters: data.parameters,
      createdAt: new Date(data.createdAt),
      updatedAt: new Date(data.updatedAt)
    });
  }
}
