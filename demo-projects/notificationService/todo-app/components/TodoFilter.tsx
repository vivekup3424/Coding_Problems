// components/TodoFilter.tsx
'use client';

import { FilterStatus } from '@/lib/types';

interface TodoFilterProps {
  currentFilter: FilterStatus;
  onFilterChange: (filter: FilterStatus) => void;
  activeCount: number;
}

const filters: { label: string; value: FilterStatus }[] = [
  { label: 'All', value: 'all' },
  { label: 'Active', value: 'active' },
  { label: 'Completed', value: 'completed' },
];

export default function TodoFilter({ currentFilter, onFilterChange, activeCount }: TodoFilterProps) {
  return (
    <div className="flex justify-between items-center mb-6 p-3 bg-slate-800 rounded-lg">
      <span className="text-sm text-slate-400">
        {activeCount} {activeCount === 1 ? 'item' : 'items'} left
      </span>
      <div className="flex gap-2">
        {filters.map((filter) => (
          <button
            key={filter.value}
            onClick={() => onFilterChange(filter.value)}
            className={`px-3 py-1 text-sm rounded-md transition-colors
              ${currentFilter === filter.value
                ? 'bg-pink-600 text-white font-semibold'
                : 'bg-slate-700 hover:bg-slate-600 text-slate-300'
              }`}
          >
            {filter.label}
          </button>
        ))}
      </div>
    </div>
  );
}