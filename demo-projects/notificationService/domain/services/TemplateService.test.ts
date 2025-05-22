import { TemplateRenderer } from "../../utils/TemplateRenderer";
import type { Template, TemplateContext } from "../../models/template";

describe("Template Domain Service", () => {
  describe("TemplateRenderer", () => {
    test("should properly render a template with valid context", () => {
      // Arrange
      const template: Template = {
        id: "test1",
        name: "Test Template",
        content: "Hello {{name}}, your order #{{orderId}} is ready at {{location}}.",
        parameters: ["name", "orderId", "location"],
        createdAt: new Date(),
        updatedAt: new Date()
      };
      
      const context: TemplateContext = {
        name: "Alice",
        orderId: "ORD-123",
        location: "Store #42"
      };
      
      // Act
      const result = TemplateRenderer.render(template, context);
      
      // Assert
      expect(result).toBe("Hello Alice, your order #ORD-123 is ready at Store #42.");
    });
    
    test("should throw an error when required parameters are missing", () => {
      // Arrange
      const template: Template = {
        id: "test2",
        name: "Test Template",
        content: "Hello {{name}}, your balance is {{amount}}.",
        parameters: ["name", "amount"],
        createdAt: new Date(),
        updatedAt: new Date()
      };
      
      const context: TemplateContext = {
        name: "Bob"
        // amount is missing
      };
      
      // Act & Assert
      expect(() => TemplateRenderer.render(template, context)).toThrow("Missing required template parameters");
    });
    
    test("should extract parameters correctly from template content", () => {
      // Arrange
      const content = "Welcome {{name}}! Your {{product}} subscription will expire on {{expiryDate}}.";
      
      // Act
      const parameters = TemplateRenderer.extractParameters(content);
      
      // Assert
      expect(parameters).toContain("name");
      expect(parameters).toContain("product");
      expect(parameters).toContain("expiryDate");
      expect(parameters.length).toBe(3);
    });
  });
});
