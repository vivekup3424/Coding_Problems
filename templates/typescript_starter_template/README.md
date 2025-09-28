# TypeScript Project

A modern TypeScript project with all essential development utilities.

## Features

- ✅ **TypeScript** - Type-safe JavaScript
- ✅ **tsx** - Fast TypeScript execution
- ✅ **ESLint** - Code linting
- ✅ **Prettier** - Code formatting
- ✅ **Jest** - Testing framework
- ✅ **Modern ES modules** - Using NodeNext module resolution

## Quick Start

### Install dependencies
```bash
npm install
```

### Development
```bash
# Run in development mode with hot reload
npm run dev

# Watch mode (auto-restart on file changes)
npm run watch
```

### Building
```bash
# Build the project
npm run build

# Run the built project
npm start
```

### Testing
```bash
# Run tests
npm test

# Run tests in watch mode
npm run test:watch
```

### Code Quality
```bash
# Lint code
npm run lint

# Fix linting issues
npm run lint:fix

# Format code
npm run format

# Type check without building
npm run typecheck
```

### Cleanup
```bash
# Clean build directory
npm run clean
```

## Project Structure

```
├── src/
│   ├── __tests__/          # Test files
│   └── index.ts            # Main entry point
├── dist/                   # Built files (generated)
├── .eslintrc.js           # ESLint configuration
├── .prettierrc            # Prettier configuration
├── jest.config.js         # Jest configuration
├── tsconfig.json          # TypeScript configuration
└── package.json           # Project dependencies and scripts
```

## Available Scripts

- `npm run dev` - Run with tsx in development mode
- `npm run watch` - Run with tsx in watch mode
- `npm run build` - Compile TypeScript to JavaScript
- `npm start` - Run the compiled JavaScript
- `npm test` - Run Jest tests
- `npm run test:watch` - Run Jest in watch mode
- `npm run lint` - Lint code with ESLint
- `npm run lint:fix` - Fix ESLint issues automatically
- `npm run format` - Format code with Prettier
- `npm run typecheck` - Run TypeScript type checking
- `npm run clean` - Remove dist directory