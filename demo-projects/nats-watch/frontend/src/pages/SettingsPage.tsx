import { useState, useEffect } from 'react';
import { Plus, Trash2, Save } from 'lucide-react';
import type { Server, LabelCategory } from '../types';
import { fetchLabels, createLabelCategory, createLabelRule, deleteLabel, deleteRule } from '../services/api';

interface SettingsPageProps {
  server: Server;
  onUpdate: () => void;
}

export default function SettingsPage({ server, onUpdate: _onUpdate }: SettingsPageProps) {
  const [categories, setCategories] = useState<LabelCategory[]>([]);
  const [newCategoryName, setNewCategoryName] = useState('');
  const [loading, setLoading] = useState(true);

  const loadLabels = async () => {
    try {
      const data = await fetchLabels(server.id);
      setCategories(data);
    } catch (e) {
      console.error('Failed to load labels:', e);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    loadLabels();
  }, [server.id]);

  const handleAddCategory = async () => {
    if (!newCategoryName.trim()) return;
    try {
      await createLabelCategory(server.id, newCategoryName.trim());
      setNewCategoryName('');
      loadLabels();
    } catch (e) {
      console.error('Failed to create category:', e);
    }
  };

  const handleDeleteCategory = async (id: number) => {
    if (!confirm('Delete this label category and all its rules?')) return;
    try {
      await deleteLabel(id);
      loadLabels();
    } catch (e) {
      console.error('Failed to delete category:', e);
    }
  };

  const handleAddRule = async (categoryId: number, labelValue: string, pattern: string) => {
    try {
      await createLabelRule(categoryId, { label_value: labelValue, pattern, priority: 0 });
      loadLabels();
    } catch (e) {
      console.error('Failed to create rule:', e);
    }
  };

  const handleDeleteRule = async (id: number) => {
    try {
      await deleteRule(id);
      loadLabels();
    } catch (e) {
      console.error('Failed to delete rule:', e);
    }
  };

  return (
    <div className="space-y-6">
      <div>
        <h2 className="text-2xl font-bold text-gray-900">Settings</h2>
        <p className="text-gray-500 mt-1">Configure labels and categorization rules</p>
      </div>

      {/* Server Info */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-6">
        <h3 className="text-lg font-semibold text-gray-900 mb-4">Server Information</h3>
        <div className="grid grid-cols-2 gap-4 text-sm">
          <div>
            <span className="text-gray-500">Name:</span>
            <span className="ml-2 font-medium">{server.name}</span>
          </div>
          <div>
            <span className="text-gray-500">URL:</span>
            <span className="ml-2 font-medium">{server.url}</span>
          </div>
          <div>
            <span className="text-gray-500">Auth Type:</span>
            <span className="ml-2 font-medium capitalize">{server.auth_type}</span>
          </div>
        </div>
      </div>

      {/* Label Categories */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-6">
        <div className="flex items-center justify-between mb-4">
          <h3 className="text-lg font-semibold text-gray-900">Label Categories</h3>
        </div>

        <p className="text-sm text-gray-500 mb-4">
          Create label categories to organize clients. Use pattern rules to automatically assign labels based on client names.
        </p>

        {/* Add Category */}
        <div className="flex gap-2 mb-6">
          <input
            type="text"
            value={newCategoryName}
            onChange={(e) => setNewCategoryName(e.target.value)}
            placeholder="Category name (e.g., Environment, Team)"
            className="flex-1 px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
            onKeyDown={(e) => e.key === 'Enter' && handleAddCategory()}
          />
          <button
            onClick={handleAddCategory}
            disabled={!newCategoryName.trim()}
            className="px-4 py-2 bg-indigo-600 text-white rounded-lg hover:bg-indigo-700 disabled:opacity-50 flex items-center gap-2"
          >
            <Plus size={18} />
            Add Category
          </button>
        </div>

        {/* Categories List */}
        {loading ? (
          <div className="text-gray-500">Loading...</div>
        ) : categories.length === 0 ? (
          <div className="text-center py-8 text-gray-500">
            No label categories yet. Create one above to get started.
          </div>
        ) : (
          <div className="space-y-4">
            {categories.map((category) => (
              <CategoryCard
                key={category.id}
                category={category}
                onDelete={() => handleDeleteCategory(category.id)}
                onAddRule={(label, pattern) => handleAddRule(category.id, label, pattern)}
                onDeleteRule={handleDeleteRule}
              />
            ))}
          </div>
        )}
      </div>
    </div>
  );
}

interface CategoryCardProps {
  category: LabelCategory;
  onDelete: () => void;
  onAddRule: (labelValue: string, pattern: string) => void;
  onDeleteRule: (id: number) => void;
}

function CategoryCard({ category, onDelete, onAddRule, onDeleteRule }: CategoryCardProps) {
  const [newLabel, setNewLabel] = useState('');
  const [newPattern, setNewPattern] = useState('');
  const [showAddRule, setShowAddRule] = useState(false);

  const handleAdd = () => {
    if (newLabel && newPattern) {
      onAddRule(newLabel, newPattern);
      setNewLabel('');
      setNewPattern('');
      setShowAddRule(false);
    }
  };

  return (
    <div className="border border-gray-200 rounded-lg p-4">
      <div className="flex items-center justify-between mb-3">
        <h4 className="font-semibold text-gray-900">{category.name}</h4>
        <button
          onClick={onDelete}
          className="p-2 text-gray-400 hover:text-red-600 transition-colors"
          title="Delete category"
        >
          <Trash2 size={16} />
        </button>
      </div>

      {/* Rules */}
      <div className="space-y-2 mb-3">
        {category.rules && category.rules.length > 0 ? (
          category.rules.map((rule) => (
            <div
              key={rule.id}
              className="flex items-center justify-between px-3 py-2 bg-gray-50 rounded-lg text-sm"
            >
              <div>
                <span className="font-medium text-indigo-600">{rule.label_value}</span>
                <span className="text-gray-500 mx-2">←</span>
                <code className="text-gray-700 bg-gray-200 px-2 py-0.5 rounded">{rule.pattern}</code>
              </div>
              <button
                onClick={() => onDeleteRule(rule.id)}
                className="p-1 text-gray-400 hover:text-red-600"
              >
                <Trash2 size={14} />
              </button>
            </div>
          ))
        ) : (
          <div className="text-sm text-gray-500 italic">No rules defined</div>
        )}
      </div>

      {/* Add Rule */}
      {showAddRule ? (
        <div className="flex gap-2 items-center">
          <input
            type="text"
            value={newLabel}
            onChange={(e) => setNewLabel(e.target.value)}
            placeholder="Label (e.g., Production)"
            className="flex-1 px-3 py-1.5 text-sm border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500"
          />
          <input
            type="text"
            value={newPattern}
            onChange={(e) => setNewPattern(e.target.value)}
            placeholder="Pattern (e.g., ^prod-.*)"
            className="flex-1 px-3 py-1.5 text-sm border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500"
          />
          <button
            onClick={handleAdd}
            disabled={!newLabel || !newPattern}
            className="p-1.5 bg-indigo-600 text-white rounded-lg hover:bg-indigo-700 disabled:opacity-50"
          >
            <Save size={16} />
          </button>
          <button
            onClick={() => setShowAddRule(false)}
            className="p-1.5 text-gray-400 hover:text-gray-600"
          >
            Cancel
          </button>
        </div>
      ) : (
        <button
          onClick={() => setShowAddRule(true)}
          className="text-sm text-indigo-600 hover:text-indigo-700 flex items-center gap-1"
        >
          <Plus size={14} />
          Add Rule
        </button>
      )}
    </div>
  );
}
