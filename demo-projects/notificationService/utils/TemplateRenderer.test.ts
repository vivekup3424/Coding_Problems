import { TemplateRenderer } from './TemplateRenderer';
import type { Template, TemplateContext } from '../models/template';

describe('TemplateRenderer', () => {
  it('should render a template with all parameters', () => {
    const template: Template = {
      id: 'test-template',
      name: 'Test Template',
      content: 'Hello {{name}}, welcome to {{service}}!',
      parameters: ['name', 'service'],
      createdAt: new Date(),
      updatedAt: new Date()
    };
    
    const context: TemplateContext = {
      name: 'John',
      service: 'Notification Service'
    };
    
    const rendered = TemplateRenderer.render(template, context);
    expect(rendered).toBe('Hello John, welcome to Notification Service!');
  });
  
  it('should throw an error when missing parameters', () => {
    const template: Template = {
      id: 'test-template',
      name: 'Test Template',
      content: 'Hello {{name}}, your {{alert_type}} notification: {{message}}',
      parameters: ['name', 'alert_type', 'message'],
      createdAt: new Date(),
      updatedAt: new Date()
    };
    
    const context: TemplateContext = {
      name: 'John',
      // Missing alert_type and message
    };
    
    expect(() => {
      TemplateRenderer.render(template, context);
    }).toThrow('Missing required template parameters');
  });
  
  it('should extract parameters from content', () => {
    const content = 'Hello {{name}}, your balance is ${{amount}} as of {{date}}';
    
    const parameters = TemplateRenderer.extractParameters(content);
    
    expect(parameters).toContain('name');
    expect(parameters).toContain('amount');
    expect(parameters).toContain('date');
    expect(parameters.length).toBe(3);
  });
  
  it('should handle parameters with whitespace', () => {
    const content = 'Hello {{ name }}, welcome to {{ service }}!';
    
    const parameters = TemplateRenderer.extractParameters(content);
    
    expect(parameters).toContain('name');
    expect(parameters).toContain('service');
    expect(parameters.length).toBe(2);
    
    const template: Template = {
      id: 'test-template',
      name: 'Test Template',
      content,
      parameters,
      createdAt: new Date(),
      updatedAt: new Date()
    };
    
    const context: TemplateContext = {
      name: 'John',
      service: 'Notification Service'
    };
    
    const rendered = TemplateRenderer.render(template, context);
    expect(rendered).toBe('Hello John, welcome to Notification Service!');
  });
  
  it('should handle non-string values in context', () => {
    const template: Template = {
      id: 'test-template',
      name: 'Test Template',
      content: 'Your account balance is {{balance}} credits. Active: {{active}}',
      parameters: ['balance', 'active'],
      createdAt: new Date(),
      updatedAt: new Date()
    };
    
    const context: TemplateContext = {
      balance: 1000,
      active: true
    };
    
    const rendered = TemplateRenderer.render(template, context);
    expect(rendered).toBe('Your account balance is 1000 credits. Active: true');
  });
});
