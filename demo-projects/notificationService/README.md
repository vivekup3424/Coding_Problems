# Notification Service - Clean Architecture Implementation

A comprehensive notification service built following Clean Architecture principles, providing a highly maintainable, testable, and framework-independent solution for managing notifications across multiple channels.

## Quick Start

To install dependencies:

```bash
bun install
```

To run the service:

```bash
bun run start
```

To run the service broker:

```bash
bun run start:broker
```

## Features

- 📝 Multi-channel notification delivery (Email, SMS, Push)
- 👥 Subscriber management with rich domain model
- 🏷️ Topic-based notification delivery
- 📄 Template management and rendering
- 🔔 Notification status tracking and read receipts
- 🧩 Domain-driven design with clean separation of concerns
- 🔌 Extensible provider system for easy integration with external services

## Architecture Overview

This project is implemented using Clean Architecture principles, with clear separation of concerns:

1. **Domain Layer**: Core business entities, rules, and interfaces
2. **Application Layer**: Use cases and application services 
3. **Infrastructure Layer**: External frameworks and technical implementations
4. **Interface Layer**: Controllers and API endpoints

For detailed architecture documentation, see [CLEAN_ARCHITECTURE.md](./CLEAN_ARCHITECTURE.md).

## Key Components

### Domain Components
- **Entities**: `NotificationEntity`, `TemplateEntity`, `SubscriberEntity`, `TopicEntity`
- **Value Objects**: `NotificationContent`
- **Events**: `DomainEvent`, `NotificationCreatedEvent`, `NotificationSentEvent`, etc.

### Application Components
- **Use Cases**: `SendNotificationUseCase`, `MarkNotificationAsReadUseCase`
- **Services**: `NotificationApplicationService`, `TopicApplicationService`, etc.

### Infrastructure Components
- **Repositories**: In-memory implementations of repository interfaces
- **Adapters**: Notification provider adapters, event adapters
- **DI Container**: Dependency injection management

### Interface Components
- **Controllers**: `NotificationController`, `SubscriberController`, `TopicController`

## Development

```bash
# Check for TypeScript errors
bun run check

# Run tests
bun run test
```

This project was built with [Bun](https://bun.sh), a fast all-in-one JavaScript runtime.
