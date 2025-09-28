import { greet } from '../index';

describe('greet function', () => {
  it('should return a greeting message', () => {
    const result = greet('World');
    expect(result).toBe('Hello, World!');
  });

  it('should work with different names', () => {
    const result = greet('TypeScript');
    expect(result).toBe('Hello, TypeScript!');
  });
});