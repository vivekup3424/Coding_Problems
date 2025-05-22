export interface Template {
  id: string;
  name: string;
  content: string;
  parameters: string[]; // The parameters expected by the template
  createdAt: Date;
  updatedAt: Date;
}

// Data used to render a template at runtime
export interface TemplateContext {
  [key: string]: string | number | boolean | null | undefined;
}
