import { useState, useMemo } from 'react';
import { useWebSocket } from '../hooks/useWebSocket';
import { Search, ChevronDown, ChevronRight, Network } from 'lucide-react';
import type { SubjectNode } from '../types';

export default function SubscriptionsPage() {
  const { subz, connz } = useWebSocket(true);
  const [search, setSearch] = useState('');
  const [expandedNodes, setExpandedNodes] = useState<Set<string>>(new Set());

  // Build subscription tree from flat list
  const subscriptionTree = useMemo(() => {
    const tree: Record<string, SubjectNode> = {};

    // Get all subscriptions from connz (more detailed)
    const allSubs = new Map<string, number>();

    connz?.connections?.forEach((conn) => {
      const subs = conn.subscriptions || conn.subscriptions_list || [];
      subs.forEach((sub) => {
        allSubs.set(sub, (allSubs.get(sub) || 0) + 1);
      });
    });

    // Also add from subz if available
    subz?.subscriptions_list?.forEach((sub) => {
      if (!allSubs.has(sub)) {
        allSubs.set(sub, 1);
      }
    });

    // Build tree
    allSubs.forEach((count, subject) => {
      const parts = subject.split('.');
      let current = tree;
      let path = '';

      parts.forEach((part, i) => {
        path = path ? `${path}.${part}` : part;
        if (!current[part]) {
          current[part] = {
            name: part,
            fullPath: path,
            subscriberCount: 0,
            children: {},
          };
        }
        if (i === parts.length - 1) {
          current[part].subscriberCount = count;
        }
        current = current[part].children;
      });
    });

    return tree;
  }, [subz, connz]);

  // Filter tree based on search
  const filteredTree = useMemo(() => {
    if (!search) return subscriptionTree;

    const searchLower = search.toLowerCase();
    const filter = (nodes: Record<string, SubjectNode>): Record<string, SubjectNode> => {
      const result: Record<string, SubjectNode> = {};
      Object.entries(nodes).forEach(([key, node]) => {
        const matchesSearch = node.fullPath.toLowerCase().includes(searchLower);
        const filteredChildren = filter(node.children);
        const hasMatchingChildren = Object.keys(filteredChildren).length > 0;

        if (matchesSearch || hasMatchingChildren) {
          result[key] = {
            ...node,
            children: filteredChildren,
          };
        }
      });
      return result;
    };

    return filter(subscriptionTree);
  }, [subscriptionTree, search]);

  const toggleNode = (path: string) => {
    setExpandedNodes((prev) => {
      const next = new Set(prev);
      if (next.has(path)) {
        next.delete(path);
      } else {
        next.add(path);
      }
      return next;
    });
  };

  const expandAll = () => {
    const allPaths = new Set<string>();
    const collect = (nodes: Record<string, SubjectNode>) => {
      Object.values(nodes).forEach((node) => {
        if (Object.keys(node.children).length > 0) {
          allPaths.add(node.fullPath);
          collect(node.children);
        }
      });
    };
    collect(filteredTree);
    setExpandedNodes(allPaths);
  };

  const collapseAll = () => {
    setExpandedNodes(new Set());
  };

  const totalSubs = subz?.num_subscriptions || connz?.connections?.reduce((acc, c) =>
    acc + (c.subscriptions?.length || c.subscriptions_list?.length || 0), 0) || 0;

  if (!subz && !connz) {
    return (
      <div className="flex items-center justify-center h-64">
        <div className="text-gray-500">Loading subscriptions...</div>
      </div>
    );
  }

  return (
    <div className="space-y-6">
      {/* Header */}
      <div className="flex items-center justify-between">
        <div>
          <h2 className="text-2xl font-bold text-gray-900">Subscriptions</h2>
          <p className="text-gray-500 mt-1">{totalSubs} total subscriptions</p>
        </div>
        <div className="flex gap-2">
          <button
            onClick={expandAll}
            className="px-4 py-2 text-sm text-gray-600 hover:bg-gray-100 rounded-lg transition-colors"
          >
            Expand All
          </button>
          <button
            onClick={collapseAll}
            className="px-4 py-2 text-sm text-gray-600 hover:bg-gray-100 rounded-lg transition-colors"
          >
            Collapse All
          </button>
        </div>
      </div>

      {/* Search */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-4">
        <div className="relative max-w-md">
          <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={18} />
          <input
            type="text"
            value={search}
            onChange={(e) => setSearch(e.target.value)}
            placeholder="Search subjects (e.g., orders.*)"
            className="w-full pl-10 pr-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
          />
        </div>
      </div>

      {/* Subscription Tree */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-6">
        {Object.keys(filteredTree).length === 0 ? (
          <div className="text-center py-12 text-gray-500">
            <Network size={48} className="mx-auto mb-4 opacity-50" />
            <p>No subscriptions found</p>
          </div>
        ) : (
          <div className="space-y-1">
            {Object.values(filteredTree).map((node) => (
              <TreeNode
                key={node.fullPath}
                node={node}
                depth={0}
                expanded={expandedNodes}
                onToggle={toggleNode}
              />
            ))}
          </div>
        )}
      </div>
    </div>
  );
}

interface TreeNodeProps {
  node: SubjectNode;
  depth: number;
  expanded: Set<string>;
  onToggle: (path: string) => void;
}

function TreeNode({ node, depth, expanded, onToggle }: TreeNodeProps) {
  const hasChildren = Object.keys(node.children).length > 0;
  const isExpanded = expanded.has(node.fullPath);

  return (
    <div>
      <button
        onClick={() => hasChildren && onToggle(node.fullPath)}
        className={`w-full flex items-center gap-2 px-3 py-2 rounded-lg hover:bg-gray-50 transition-colors text-left ${
          hasChildren ? 'cursor-pointer' : 'cursor-default'
        }`}
        style={{ paddingLeft: `${depth * 24 + 12}px` }}
      >
        {hasChildren ? (
          isExpanded ? (
            <ChevronDown size={16} className="text-gray-400 flex-shrink-0" />
          ) : (
            <ChevronRight size={16} className="text-gray-400 flex-shrink-0" />
          )
        ) : (
          <span className="w-4 flex-shrink-0" />
        )}
        <span className="font-mono text-sm text-gray-900 flex-1 truncate">
          {node.name}
        </span>
        {node.subscriberCount > 0 && (
          <span className="px-2 py-0.5 bg-indigo-100 text-indigo-700 text-xs rounded-full flex-shrink-0">
            {node.subscriberCount} subscriber{node.subscriberCount !== 1 ? 's' : ''}
          </span>
        )}
      </button>
      {hasChildren && isExpanded && (
        <div>
          {Object.values(node.children).map((child) => (
            <TreeNode
              key={child.fullPath}
              node={child}
              depth={depth + 1}
              expanded={expanded}
              onToggle={onToggle}
            />
          ))}
        </div>
      )}
    </div>
  );
}
