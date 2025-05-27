<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

# Knowledge Graph Project - Copilot Instructions

This is a Python-based knowledge graph project using Neo4j for learning graph database concepts. When providing code assistance:

## Project Structure Guidelines
- Use proper typing annotations for all Python functions
- Follow PEP 8 style guidelines
- Prefer object-oriented design patterns for graph operations
- Use dependency injection for database connections
- Include comprehensive docstrings for all classes and methods

## Graph Database Patterns
- When working with Neo4j queries, use parameterized Cypher queries
- Implement proper error handling for database operations
- Use transaction boundaries for complex operations
- Follow graph database best practices for node and relationship naming

## Data Modeling Conventions
- Node labels should be singular and PascalCase (e.g., Person, Organization)
- Relationship types should be ALL_CAPS with underscores (e.g., WORKS_FOR, KNOWS)
- Property names should be camelCase
- Use UUIDs for node identifiers when appropriate

## Testing Standards
- Write unit tests for all graph operations
- Use pytest fixtures for database setup/teardown
- Mock external dependencies in tests
- Include integration tests for complete workflows

## Documentation
- Provide clear examples in docstrings
- Include type hints for better IDE support
- Comment complex Cypher queries thoroughly
- Maintain educational focus with clear explanations
