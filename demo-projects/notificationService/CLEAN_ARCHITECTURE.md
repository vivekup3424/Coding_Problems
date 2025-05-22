# Notification Service - Clean Architecture Implementation

This project implements a notification service following Clean Architecture principles. The refactoring has transformed the service into a well-organized, maintainable system with clear separation of concerns.

## Architecture Overview

The application is structured in layers according to Clean Architecture:

### 1. Domain Layer
- **Entities**: `NotificationEntity`, `TemplateEntity`, `SubscriberEntity`, `TopicEntity` with rich business behavior
- **Value Objects**: `NotificationContent` for provider-specific content
- **Domain Events**: `NotificationCreatedEvent`, `NotificationSentEvent`, `NotificationFailedEvent`, `NotificationReadEvent`
- **Repository Interfaces**: `INotificationRepository`, `ITemplateRepository`, `ISubscriberRepository`, `ITopicRepository`
- **Domain Services**: `NotificationDomainService` for core business logic
- **Ports**: `INotificationProvider` defining adapter interfaces for output ports

### 2. Application Layer
- **Use Cases**: `SendNotificationUseCase`, `MarkNotificationAsReadUseCase`
- **Application Services**: `NotificationApplicationService`, `TemplateApplicationService`, `SubscriberApplicationService`, `TopicApplicationService`
- **Input/Output Models**: Request/response models for use cases

### 3. Infrastructure Layer
- **Repository Implementations**: `InMemoryNotificationRepository`, `InMemoryTemplateRepository`, `InMemorySubscriberRepository`, `InMemoryTopicRepository`
- **Adapters**: 
  - Event handling: `MoleculerEventAdapter`
  - Notification providers: `EmailProviderAdapter`, `SMSProviderAdapter`, `PushProviderAdapter`
  - Legacy adapters: `NotificationProviderAdapter`
- **Provider Registry**: `ProviderRegistry` for managing notification providers
- **DI Container**: `Container` for dependency injection
- **Bootstrap**: Service configuration and initialization

### 4. Interfaces Layer
- **API Controllers**: `NotificationController`, `SubscriberController`, `TopicController` for handling API requests
- **Request Models**: Input data models for controllers

## Clean Architecture Benefits

1. **Separation of Concerns**: Each layer has a specific responsibility
2. **Dependency Rule**: Dependencies always point inward
3. **Testability**: Business logic can be tested without external dependencies
4. **Framework Independence**: Core business logic doesn't depend on frameworks
5. **Maintainability**: Changes in one layer have minimal impact on others

## Key Design Patterns & Principles

### Design Patterns
- **Repository Pattern**: Abstracts data access through clear interfaces
- **Dependency Injection**: Decouples components via Container
- **Adapter Pattern**: Adapts external services to domain interfaces
- **Observer Pattern**: Via domain events system
- **Factory Methods**: Creates domain entities with proper validation

### SOLID Principles
- **Single Responsibility**: Each class has one reason to change
- **Open/Closed**: Extend behavior without modifying (e.g., adding new notification providers)
- **Liskov Substitution**: Repository implementations can substitute for interfaces
- **Interface Segregation**: Specific interfaces for specific clients
- **Dependency Inversion**: High-level modules depend on abstractions (e.g., repositories)

## Domain-Driven Design Elements

- **Rich Domain Models**: Entities with behavior, not just data
- **Value Objects**: Immutable objects representing domain concepts
- **Domain Events**: Representing significant occurrences in the domain
- **Repositories**: Collection-like interfaces for entity persistence
- **Domain Services**: Logic that doesn't fit in entities

## Running the Application

```bash
# Install dependencies
bun install

# Start the main service
bun run start

# Start only the broker
bun run start:broker

# Check for TypeScript errors
bun run check

# Run tests
bun run test
```

## Current Project Structure

```
notification-service/
├── domain/                        # Enterprise business rules
│   ├── entities/                  # Rich domain entities
│   │   ├── NotificationEntity.ts
│   │   ├── TemplateEntity.ts
│   │   ├── SubscriberEntity.ts
│   │   └── TopicEntity.ts
│   ├── events/                    # Domain events
│   │   ├── DomainEvent.ts
│   │   └── DomainEventPublisher.ts
│   ├── ports/                     # Ports for external adapters
│   │   └── INotificationProvider.ts
│   ├── repositories/              # Repository interfaces
│   │   ├── INotificationRepository.ts
│   │   ├── ITemplateRepository.ts
│   │   ├── ISubscriberRepository.ts
│   │   └── ITopicRepository.ts
│   ├── services/                  # Domain services
│   │   └── NotificationDomainService.ts
│   └── valueObjects/              # Value objects
│       └── NotificationContent.ts
├── application/                   # Application business rules
│   ├── services/                  # Application services
│   │   ├── NotificationApplicationService.ts
│   │   ├── TemplateApplicationService.ts
│   │   ├── SubscriberApplicationService.ts
│   │   └── TopicApplicationService.ts
│   └── useCases/                  # Use case implementations
│       ├── MarkNotificationAsReadUseCase.ts
│       └── SendNotificationUseCase.ts
├── infrastructure/                # Frameworks and tools
│   ├── adapters/                  # External adapters
│   │   ├── MoleculerEventAdapter.ts
│   │   ├── NotificationProviderAdapter.ts
│   │   └── providers/             # Provider implementations
│   │       ├── EmailProviderAdapter.ts
│   │       ├── SMSProviderAdapter.ts
│   │       ├── PushProviderAdapter.ts
│   │       ├── ProviderRegistry.ts
│   │       └── index.ts
│   ├── di/                        # Dependency injection
│   │   └── Container.ts
│   ├── repositories/              # Repository implementations
│   │   ├── InMemoryNotificationRepository.ts
│   │   ├── InMemoryTemplateRepository.ts
│   │   ├── InMemorySubscriberRepository.ts
│   │   └── InMemoryTopicRepository.ts
│   └── bootstrap.ts               # Application bootstrap
├── interfaces/                    # Interface adapters
│   └── api/                       # API controllers
│       ├── NotificationController.ts
│       ├── SubscriberController.ts
│       └── TopicController.ts
├── models/                        # Shared data models
│   ├── notification.ts
│   ├── subscriber.ts
│   ├── template.ts
│   └── topic.ts
├── utils/                         # Utility functions
│   ├── BloomFilter.ts
│   └── TemplateRenderer.ts
└── index.ts                       # Application entry point
└── broker.ts                      # Service broker entry point
```

## Migration Summary

The refactoring of the notification service to follow Clean Architecture principles has successfully transformed a monolithic, tightly-coupled service into a modular, maintainable system with clear separation of concerns. Here's a summary of the key improvements:

### Completed Migrations

1. **Core Domain Layer**
   - Rich domain entities with encapsulated behavior
   - Repository interfaces defining data access contracts
   - Domain events for decoupled communication
   - Value objects for immutable domain concepts

2. **Application Layer**
   - Use cases implementing business processes
   - Application services coordinating domain operations
   - Clear input/output boundaries

3. **Infrastructure Layer**
   - Repository implementations with in-memory storage
   - Provider adapters for external integrations
   - Dependency injection container
   - Event handling with Moleculer integration

4. **Interface Layer**
   - Controllers for handling API requests
   - Service endpoints for external communication

### Benefits Achieved

1. **Maintainability**
   - Clear separation of concerns makes code easier to understand
   - Domain logic isolated from external dependencies
   - Changes in one layer have minimal impact on others

2. **Testability**
   - Business rules can be tested without external dependencies
   - Mock implementations can replace infrastructure components
   - Domain services can be tested in isolation

3. **Flexibility**
   - Easy to add new notification channels
   - Simple to replace external services
   - Framework-independent core business logic

4. **Scalability**
   - Clean boundaries allow for distributed deployment
   - Services can be scaled independently
   - Event-driven architecture enables asynchronous processing

### Future Enhancements

1. **Persistence Layer**
   - Implement database repositories
   - Add data migration utilities
   - Optimize query performance

2. **Authentication & Authorization**
   - Add permission checks to use cases
   - Implement role-based access control
   - Add audit logging for sensitive operations

3. **Monitoring & Observability**
   - Add metrics collection
   - Implement distributed tracing
   - Enhance error reporting and diagnostics

4. **Additional Notification Channels**
   - Web push notifications
   - In-app notifications
   - Social media integrations
