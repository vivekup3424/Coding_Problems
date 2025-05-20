// app/page.tsx
'use client'; // This is crucial for using hooks like useState and useEffect

import { useState, useEffect, useMemo } from 'react';
import { Todo, FilterStatus } from '@/lib/types';
import TodoForm from '@/components/TodoForm';
import TodoList from '@/components/TodoList';
import TodoFilter from '@/components/TodoFilter';
import Inbox from "@/components/Inbox";
import { ListTodo } from 'lucide-react';

const LOCAL_STORAGE_KEY = 'nextjs-todo-app';

export default function HomePage() {
  const [todos, setTodos] = useState<Todo[]>([]);
  const [filter, setFilter] = useState<FilterStatus>('all');

  // Load todos from localStorage on initial mount
  useEffect(() => {
    const storedTodos = localStorage.getItem(LOCAL_STORAGE_KEY);
    if (storedTodos) {
      setTodos(JSON.parse(storedTodos));
    }
  }, []);

  // Save todos to localStorage whenever they change
  useEffect(() => {
    if (todos.length > 0 || localStorage.getItem(LOCAL_STORAGE_KEY)) { // Only save if todos exist or existed before
        localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(todos));
    }
  }, [todos]);

  const addTodo = (text: string) => {
    const newTodo: Todo = {
      id: crypto.randomUUID(), // Modern way to generate UUIDs
      text,
      completed: false,
    };
    setTodos((prevTodos) => [newTodo, ...prevTodos]);
  };

  const toggleComplete = (id: string) => {
    setTodos((prevTodos) =>
      prevTodos.map((todo) =>
        todo.id === id ? { ...todo, completed: !todo.completed } : todo
      )
    );
  };

  const deleteTodo = (id: string) => {
    setTodos((prevTodos) => prevTodos.filter((todo) => todo.id !== id));
  };

  const filteredTodos = useMemo(() => {
    switch (filter) {
      case 'active':
        return todos.filter((todo) => !todo.completed);
      case 'completed':
        return todos.filter((todo) => todo.completed);
      default:
        return todos;
    }
  }, [todos, filter]);

  const activeCount = useMemo(() => todos.filter(todo => !todo.completed).length, [todos]);

  return (
    <div className="bg-slate-800/50 shadow-2xl rounded-xl p-6 md:p-8">
      <header className="mb-8 text-center">
      <Inbox />
        <h1 className="text-4xl font-bold text-pink-500 flex items-center justify-center gap-3">
          <ListTodo size={40} /> My Awesome Todos
        </h1>
        <p className="text-slate-400 mt-2">Organize your tasks efficiently!</p>
      </header>

      <TodoForm onAddTodo={addTodo} />

      {todos.length > 0 && ( // Only show filter if there are todos
        <TodoFilter 
            currentFilter={filter} 
            onFilterChange={setFilter} 
            activeCount={activeCount}
        />
      )}

      <TodoList
        todos={filteredTodos}
        onToggleComplete={toggleComplete}
        onDelete={deleteTodo}
      />

      {todos.length > 0 && filter === 'completed' && filteredTodos.length > 0 && (
        <button
          onClick={() => setTodos(prev => prev.filter(t => !t.completed))}
          className="mt-6 w-full text-sm text-slate-500 hover:text-red-400 transition-colors py-2 rounded-lg border border-slate-700 hover:border-red-500"
        >
          Clear Completed Tasks
        </button>
      )}
    </div>
  );
}