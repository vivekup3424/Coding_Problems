// components/TodoForm.tsx
'use client';

import { PlusCircle } from 'lucide-react';
import { useState, FormEvent } from 'react';

interface TodoFormProps {
  onAddTodo: (text: string) => void;
}

export default function TodoForm({ onAddTodo }: TodoFormProps) {
  const [newTodoText, setNewTodoText] = useState('');

  const handleSubmit = (e: FormEvent) => {
    e.preventDefault();
    if (newTodoText.trim() === '') return;
    onAddTodo(newTodoText.trim());
    setNewTodoText('');
  };

  return (
    <form onSubmit={handleSubmit} className="flex items-center gap-3 mb-8">
      <input
        type="text"
        value={newTodoText}
        onChange={(e) => setNewTodoText(e.target.value)}
        placeholder="What needs to be done?"
        className="flex-grow p-3 bg-slate-800 border border-slate-700 rounded-lg focus:ring-2 focus:ring-pink-500 focus:border-pink-500 outline-none transition-all"
      />
      <button
        type="submit"
        className="bg-pink-600 hover:bg-pink-700 text-white font-semibold p-3 rounded-lg flex items-center gap-2 transition-colors"
      >
        <PlusCircle size={20} />
        Add
      </button>
    </form>
  );
}