import type { Template, TemplateContext } from "../models/template";

export class TemplateRenderer {
  static render(template: Template, context: TemplateContext): string {
    const missingParams = this.validateContext(template, context);
    if (missingParams.length > 0) {
      throw new Error(`Missing required template parameters: ${missingParams.join(', ')}`);
    }
    
    //string substitution
    let content = template.content;
    for (const param of template.parameters) {
      const value = context[param];
      const regex = new RegExp(`\\{\\{\\s*${param}\\s*\\}\\}`, 'g');
      content = content.replace(regex, String(value));
    }
    
    return content;
  }
  
  /**
   * Validates that all required parameters are present in the context
   * 
   * @param template The template to validate against
   * @param context The context to validate
   * @returns Array of missing parameter names (empty if all are present)
   */
  static validateContext(template: Template, context: TemplateContext): string[] {
    const missingParams: string[] = [];
    
    for (const param of template.parameters) {
      if (context[param] === undefined) {
        missingParams.push(param);
      }
    }
    
    return missingParams;
  }
  
  /**
   * Extracts parameter names from a template content string
   * Looks for patterns like {{paramName}} or {{ paramName }}
   * 
   * @param content The template content string
   * @returns Array of parameter names found in the content
   */
  static extractParameters(content: string): string[] {
    const parameterRegex = /\{\{\s*([a-zA-Z0-9_]+)\s*\}\}/g;
    const parameters: Set<string> = new Set();
    
    let match: RegExpExecArray | null;
    while ((match = parameterRegex.exec(content)) !== null) {
      parameters.add(match[1]);
    }
    
    return Array.from(parameters);
  }
}
