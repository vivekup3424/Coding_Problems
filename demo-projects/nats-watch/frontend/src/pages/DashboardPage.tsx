import { useWebSocket } from '../hooks/useWebSocket';
import { Activity, Users, ArrowDownToLine, ArrowUpFromLine, Cpu, HardDrive, AlertTriangle, Wifi, WifiOff } from 'lucide-react';

function formatBytes(bytes: number): string {
  if (bytes === 0) return '0 B';
  const k = 1024;
  const sizes = ['B', 'KB', 'MB', 'GB', 'TB'];
  const i = Math.floor(Math.log(bytes) / Math.log(k));
  return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
}

function formatNumber(num: number): string {
  if (num >= 1000000) return (num / 1000000).toFixed(1) + 'M';
  if (num >= 1000) return (num / 1000).toFixed(1) + 'K';
  return num.toString();
}

interface MetricCardProps {
  title: string;
  value: string | number;
  icon: React.ReactNode;
  tooltip: string;
  status?: 'good' | 'warning' | 'error';
}

function MetricCard({ title, value, icon, tooltip, status = 'good' }: MetricCardProps) {
  const statusColors = {
    good: 'text-green-600 bg-green-50',
    warning: 'text-yellow-600 bg-yellow-50',
    error: 'text-red-600 bg-red-50',
  };

  return (
    <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-6 hover:shadow-md transition-shadow">
      <div className="flex items-start justify-between">
        <div>
          <p className="text-sm font-medium text-gray-500 flex items-center gap-1">
            {title}
            <span className="cursor-help" title={tooltip}>
              <span className="inline-flex items-center justify-center w-4 h-4 text-xs text-gray-400 border border-gray-300 rounded-full">?</span>
            </span>
          </p>
          <p className="text-3xl font-bold text-gray-900 mt-2">{value}</p>
        </div>
        <div className={`p-3 rounded-lg ${statusColors[status]}`}>
          {icon}
        </div>
      </div>
    </div>
  );
}

export default function DashboardPage() {
  const { varz, connz, connected, error } = useWebSocket(true);

  if (error) {
    return (
      <div className="bg-red-50 border border-red-200 rounded-lg p-4 text-red-700">
        <div className="flex items-center gap-2">
          <AlertTriangle size={20} />
          <span>{error}</span>
        </div>
      </div>
    );
  }

  if (!varz) {
    return (
      <div className="flex items-center justify-center h-64">
        <div className="text-gray-500">Loading metrics...</div>
      </div>
    );
  }

  const slowConsumerStatus = varz.slow_consumers > 0 ? 'error' : 'good';
  const cpuStatus = varz.cpu > 80 ? 'error' : varz.cpu > 60 ? 'warning' : 'good';
  const memBytes = varz.mem || 0;
  const memMB = memBytes / (1024 * 1024);
  const memStatus = memMB > 1024 ? 'warning' : 'good';

  return (
    <div className="space-y-6">
      {/* Server Info Header */}
      <div className="bg-white rounded-xl shadow-sm border border-gray-200 p-6">
        <div className="flex items-center justify-between">
          <div>
            <h2 className="text-2xl font-bold text-gray-900">{varz.server_name || 'NATS Server'}</h2>
            <div className="flex items-center gap-4 mt-2 text-sm text-gray-500">
              <span>Version: {varz.version}</span>
              <span>Uptime: {varz.uptime}</span>
            </div>
          </div>
          <div className={`flex items-center gap-2 px-4 py-2 rounded-full ${connected ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700'}`}>
            {connected ? <Wifi size={18} /> : <WifiOff size={18} />}
            <span className="font-medium">{connected ? 'Connected' : 'Disconnected'}</span>
          </div>
        </div>
      </div>

      {/* Metrics Grid */}
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
        <MetricCard
          title="Connected Clients"
          value={formatNumber(connz?.num_connections || varz.connections)}
          icon={<Users size={24} />}
          tooltip="Number of clients currently connected to this NATS server"
        />
        <MetricCard
          title="Messages Received"
          value={formatNumber(varz.in_msgs)}
          icon={<ArrowDownToLine size={24} />}
          tooltip="Total messages received by the server since startup"
        />
        <MetricCard
          title="Messages Sent"
          value={formatNumber(varz.out_msgs)}
          icon={<ArrowUpFromLine size={24} />}
          tooltip="Total messages sent by the server since startup"
        />
        <MetricCard
          title="Data Received"
          value={formatBytes(varz.in_bytes)}
          icon={<ArrowDownToLine size={24} />}
          tooltip="Total data received by the server"
        />
        <MetricCard
          title="Data Sent"
          value={formatBytes(varz.out_bytes)}
          icon={<ArrowUpFromLine size={24} />}
          tooltip="Total data sent by the server"
        />
        <MetricCard
          title="Slow Consumers"
          value={varz.slow_consumers}
          icon={<AlertTriangle size={24} />}
          tooltip="Clients that are not keeping up with message delivery (should be 0)"
          status={slowConsumerStatus}
        />
        <MetricCard
          title="CPU Usage"
          value={`${varz.cpu.toFixed(1)}%`}
          icon={<Cpu size={24} />}
          tooltip="Server CPU utilization percentage"
          status={cpuStatus}
        />
        <MetricCard
          title="Memory Usage"
          value={formatBytes(memBytes)}
          icon={<HardDrive size={24} />}
          tooltip="Server memory consumption"
          status={memStatus}
        />
        <MetricCard
          title="Total Connections"
          value={formatNumber(varz.total_connections)}
          icon={<Activity size={24} />}
          tooltip="Total connections since server started (including disconnected)"
        />
      </div>
    </div>
  );
}
