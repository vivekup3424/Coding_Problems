// components/TodoItem.tsx
'use client';

import { Todo } from '@/lib/types';
import { Trash2, CheckCircle, Circle } from 'lucide-react';

interface TodoItemProps {
  todo: Todo;
  onToggleComplete: (id: string) => void;
  onDelete: (id: string) => void;
}

export default function TodoItem({ todo, onToggleComplete, onDelete }: TodoItemProps) {
  return (
    <li
      className={`flex items-center justify-between p-4 mb-2 rounded-lg transition-all
                  ${todo.completed ? 'bg-slate-800 opacity-60' : 'bg-slate-700 hover:bg-slate-600'}`}
    >
      <div className="flex items-center gap-3">
        <button
          onClick={() => onToggleComplete(todo.id)}
          aria-label={todo.completed ? "Mark as incomplete" : "Mark as complete"}
          className="focus:outline-none focus:ring-2 focus:ring-pink-500 rounded-full"
        >
          {todo.completed ? (
            <CheckCircle size={24} className="text-green-500" />
          ) : (
            <Circle size={24} className="text-slate-500 hover:text-slate-400" />
          )}
        </button>
        <span
          className={`text-lg ${todo.completed ? 'line-through text-slate-500' : 'text-slate-100'}`}
        >
          {todo.text}
        </span>
      </div>
      <button
        onClick={() => onDelete(todo.id)}
        className="text-slate-500 hover:text-red-500 p-1 rounded focus:outline-none focus:ring-2 focus:ring-red-500 transition-colors"
        aria-label="Delete todo"
      >
        <Trash2 size={20} />
      </button>
    </li>
  );
}