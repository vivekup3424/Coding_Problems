import { useState, useMemo } from 'react';
import { useWebSocket } from '../hooks/useWebSocket';
import { Search, Filter, ChevronDown, ChevronRight } from 'lucide-react';
import type { Server, Connection } from '../types';

interface ClientsPageProps {
  server: Server; // eslint-disable-line @typescript-eslint/no-unused-vars
}

type GroupBy = 'none' | 'version' | 'lang' | 'ip';

export default function ClientsPage({ server: _server }: ClientsPageProps) {
  const { connz } = useWebSocket(true);
  const [search, setSearch] = useState('');
  const [groupBy, setGroupBy] = useState<GroupBy>('version');
  const [expandedGroups, setExpandedGroups] = useState<Set<string>>(new Set());

  const filteredConnections = useMemo(() => {
    if (!connz?.connections) return [];
    return connz.connections.filter((conn) => {
      const searchLower = search.toLowerCase();
      return (
        conn.name?.toLowerCase().includes(searchLower) ||
        conn.ip?.toLowerCase().includes(searchLower) ||
        conn.lang?.toLowerCase().includes(searchLower) ||
        conn.version?.toLowerCase().includes(searchLower)
      );
    });
  }, [connz, search]);

  const groupedConnections = useMemo(() => {
    if (groupBy === 'none') return { 'All Clients': filteredConnections };

    const groups: Record<string, Connection[]> = {};
    filteredConnections.forEach((conn) => {
      let key: string;
      switch (groupBy) {
        case 'version':
          key = `${conn.lang || 'unknown'} v${conn.version || 'unknown'}`;
          break;
        case 'lang':
          key = conn.lang || 'unknown';
          break;
        case 'ip':
          key = conn.ip || 'unknown';
          break;
        default:
          key = 'All';
      }
      if (!groups[key]) groups[key] = [];
      groups[key].push(conn);
    });

    // Sort groups by count (descending)
    return Object.fromEntries(
      Object.entries(groups).sort((a, b) => b[1].length - a[1].length)
    );
  }, [filteredConnections, groupBy]);

  const toggleGroup = (group: string) => {
    setExpandedGroups((prev) => {
      const next = new Set(prev);
      if (next.has(group)) {
        next.delete(group);
      } else {
        next.add(group);
      }
      return next;
    });
  };

  if (!connz) {
    return (
      <div className="flex items-center justify-center h-64">
        <div className="text-gray-500">Loading clients...</div>
      </div>
    );
  }

  return (
    <div className="space-y-6">
      {/* Header */}
      <div className="flex items-center justify-between">
        <div>
          <h2 className="text-2xl font-bold text-gray-900">Connected Clients</h2>
          <p className="text-gray-500 mt-1">{connz.num_connections} clients connected</p>
        </div>
      </div>

      {/* Filters */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-4">
        <div className="flex flex-wrap items-center gap-4">
          {/* Search */}
          <div className="flex-1 min-w-64">
            <div className="relative">
              <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={18} />
              <input
                type="text"
                value={search}
                onChange={(e) => setSearch(e.target.value)}
                placeholder="Search by name, IP, language..."
                className="w-full pl-10 pr-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
              />
            </div>
          </div>

          {/* Group By */}
          <div className="flex items-center gap-2">
            <Filter size={18} className="text-gray-400" />
            <span className="text-sm text-gray-600">Group by:</span>
            <select
              value={groupBy}
              onChange={(e) => setGroupBy(e.target.value as GroupBy)}
              className="px-3 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500 text-sm"
            >
              <option value="none">None</option>
              <option value="version">Client Version</option>
              <option value="lang">Language</option>
              <option value="ip">IP Address</option>
            </select>
          </div>
        </div>
      </div>

      {/* Client Groups */}
      <div className="space-y-4">
        {Object.entries(groupedConnections).map(([group, connections]) => (
          <div key={group} className="bg-white rounded-xl shadow-sm border border-gray-200 overflow-hidden">
            {/* Group Header */}
            <button
              onClick={() => toggleGroup(group)}
              className="w-full px-6 py-4 flex items-center justify-between hover:bg-gray-50 transition-colors"
            >
              <div className="flex items-center gap-3">
                {expandedGroups.has(group) || groupBy === 'none' ? (
                  <ChevronDown size={20} className="text-gray-400" />
                ) : (
                  <ChevronRight size={20} className="text-gray-400" />
                )}
                <span className="font-semibold text-gray-900">{group}</span>
                <span className="px-2 py-1 bg-gray-100 text-gray-600 text-sm rounded-full">
                  {connections.length} clients
                </span>
              </div>
            </button>

            {/* Client List */}
            {(expandedGroups.has(group) || groupBy === 'none') && (
              <div className="border-t border-gray-200">
                <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4 p-4">
                  {connections.map((conn) => (
                    <ClientCard key={conn.cid} client={conn} />
                  ))}
                </div>
              </div>
            )}
          </div>
        ))}
      </div>

      {filteredConnections.length === 0 && (
        <div className="text-center py-12 text-gray-500">
          No clients found matching your search.
        </div>
      )}
    </div>
  );
}

function ClientCard({ client }: { client: Connection }) {
  const subsCount = client.subscriptions?.length || client.subscriptions_list?.length || 0;

  return (
    <div className="p-4 bg-gray-50 rounded-lg hover:bg-gray-100 transition-colors">
      <div className="font-medium text-gray-900 truncate" title={client.name}>
        {client.name || `Client ${client.cid}`}
      </div>
      <div className="mt-2 space-y-1 text-sm text-gray-500">
        <div className="flex justify-between">
          <span>Version:</span>
          <span className="font-medium text-gray-700">{client.lang} {client.version}</span>
        </div>
        <div className="flex justify-between">
          <span>IP:</span>
          <span className="font-medium text-gray-700">{client.ip}:{client.port}</span>
        </div>
        <div className="flex justify-between">
          <span>Uptime:</span>
          <span className="font-medium text-gray-700">{client.uptime}</span>
        </div>
        <div className="flex justify-between">
          <span>Subscriptions:</span>
          <span className="font-medium text-gray-700">{subsCount}</span>
        </div>
        <div className="flex justify-between">
          <span>Msgs In/Out:</span>
          <span className="font-medium text-gray-700">{client.in_msgs} / {client.out_msgs}</span>
        </div>
      </div>
    </div>
  );
}
