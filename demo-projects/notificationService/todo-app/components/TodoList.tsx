// components/TodoList.tsx
'use client';

import { Todo } from '@/lib/types';
import TodoItem from './TodoItem';

interface TodoListProps {
  todos: Todo[];
  onToggleComplete: (id: string) => void;
  onDelete: (id: string) => void;
}

export default function TodoList({ todos, onToggleComplete, onDelete }: TodoListProps) {
  if (todos.length === 0) {
    return (
      <p className="text-center text-slate-500 py-8">
        No todos yet. Add one above!
      </p>
    );
  }

  return (
    <ul>
      {todos.map((todo) => (
        <TodoItem
          key={todo.id}
          todo={todo}
          onToggleComplete={onToggleComplete}
          onDelete={onDelete}
        />
      ))}
    </ul>
  );
}