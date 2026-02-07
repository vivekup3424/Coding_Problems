import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { Server, Loader2, CheckCircle, XCircle, Trash2 } from 'lucide-react';
import type { Server as ServerType, AuthType } from '../types';
import { createServer, activateServer, testServer, deleteServer } from '../services/api';

interface ConnectionPageProps {
  servers: ServerType[];
  onServersChange: () => void;
}

export default function ConnectionPage({ servers, onServersChange }: ConnectionPageProps) {
  const navigate = useNavigate();
  const [name, setName] = useState('');
  const [url, setUrl] = useState('');
  const [authType, setAuthType] = useState<AuthType>('none');
  const [token, setToken] = useState('');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [loading, setLoading] = useState(false);
  const [testResult, setTestResult] = useState<{ success: boolean; message: string } | null>(null);

  const handleConnect = async () => {
    if (!name || !url) return;

    setLoading(true);
    setTestResult(null);

    try {
      const server = await createServer({
        name,
        url,
        auth_type: authType,
        auth_token: authType === 'token' ? token : undefined,
        auth_username: authType === 'userpass' ? username : undefined,
        auth_password: authType === 'userpass' ? password : undefined,
      });

      // Test the connection
      const result = await testServer(server.id);
      if (result.success) {
        await activateServer(server.id);
        onServersChange();
        navigate('/');
      } else {
        setTestResult({ success: false, message: result.error || 'Connection failed' });
        await deleteServer(server.id);
      }
    } catch (e) {
      setTestResult({ success: false, message: 'Failed to create server' });
    } finally {
      setLoading(false);
    }
  };

  const handleSelectServer = async (server: ServerType) => {
    setLoading(true);
    try {
      const result = await testServer(server.id);
      if (result.success) {
        await activateServer(server.id);
        onServersChange();
        navigate('/');
      } else {
        setTestResult({ success: false, message: result.error || 'Connection failed' });
      }
    } catch (e) {
      setTestResult({ success: false, message: 'Connection failed' });
    } finally {
      setLoading(false);
    }
  };

  const handleDeleteServer = async (e: React.MouseEvent, id: number) => {
    e.stopPropagation();
    if (confirm('Delete this server?')) {
      await deleteServer(id);
      onServersChange();
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-indigo-50 to-blue-50 flex items-center justify-center p-4">
      <div className="w-full max-w-md">
        <div className="text-center mb-8">
          <div className="inline-flex items-center justify-center w-16 h-16 bg-indigo-600 rounded-2xl mb-4">
            <Server className="w-8 h-8 text-white" />
          </div>
          <h1 className="text-3xl font-bold text-gray-900">NATSWatch</h1>
          <p className="text-gray-600 mt-2">Connect to your NATS server to get started</p>
        </div>

        <div className="bg-white rounded-2xl shadow-xl p-6">
          <div className="space-y-4">
            <div>
              <label className="block text-sm font-medium text-gray-700 mb-1">
                Server Name
              </label>
              <input
                type="text"
                value={name}
                onChange={(e) => setName(e.target.value)}
                placeholder="My NATS Server"
                className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
              />
            </div>

            <div>
              <label className="block text-sm font-medium text-gray-700 mb-1">
                Monitoring URL
              </label>
              <input
                type="text"
                value={url}
                onChange={(e) => setUrl(e.target.value)}
                placeholder="http://nats-server:8222"
                className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
              />
              <p className="text-xs text-gray-500 mt-1">
                The NATS monitoring endpoint (usually port 8222)
              </p>
            </div>

            <div>
              <label className="block text-sm font-medium text-gray-700 mb-2">
                Authentication
              </label>
              <div className="flex gap-2">
                {(['none', 'token', 'userpass'] as AuthType[]).map((type) => (
                  <button
                    key={type}
                    onClick={() => setAuthType(type)}
                    className={`flex-1 px-4 py-2 text-sm font-medium rounded-lg border transition-colors ${
                      authType === type
                        ? 'bg-indigo-50 border-indigo-500 text-indigo-700'
                        : 'border-gray-300 text-gray-700 hover:bg-gray-50'
                    }`}
                  >
                    {type === 'none' ? 'None' : type === 'token' ? 'Token' : 'User/Pass'}
                  </button>
                ))}
              </div>
            </div>

            {authType === 'token' && (
              <div>
                <label className="block text-sm font-medium text-gray-700 mb-1">
                  Token
                </label>
                <input
                  type="password"
                  value={token}
                  onChange={(e) => setToken(e.target.value)}
                  placeholder="Enter your auth token"
                  className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
                />
              </div>
            )}

            {authType === 'userpass' && (
              <>
                <div>
                  <label className="block text-sm font-medium text-gray-700 mb-1">
                    Username
                  </label>
                  <input
                    type="text"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                    placeholder="Username"
                    className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
                  />
                </div>
                <div>
                  <label className="block text-sm font-medium text-gray-700 mb-1">
                    Password
                  </label>
                  <input
                    type="password"
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                    placeholder="Password"
                    className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500"
                  />
                </div>
              </>
            )}

            {testResult && (
              <div
                className={`flex items-center gap-2 p-3 rounded-lg ${
                  testResult.success ? 'bg-green-50 text-green-700' : 'bg-red-50 text-red-700'
                }`}
              >
                {testResult.success ? <CheckCircle size={18} /> : <XCircle size={18} />}
                <span className="text-sm">{testResult.message}</span>
              </div>
            )}

            <button
              onClick={handleConnect}
              disabled={loading || !name || !url}
              className="w-full py-3 px-4 bg-indigo-600 text-white font-medium rounded-lg hover:bg-indigo-700 disabled:opacity-50 disabled:cursor-not-allowed flex items-center justify-center gap-2"
            >
              {loading ? (
                <>
                  <Loader2 className="animate-spin" size={18} />
                  Connecting...
                </>
              ) : (
                'Connect'
              )}
            </button>
          </div>

          {servers.length > 0 && (
            <div className="mt-6 pt-6 border-t border-gray-200">
              <h3 className="text-sm font-medium text-gray-700 mb-3">Saved Servers</h3>
              <div className="space-y-2">
                {servers.map((server) => (
                  <div
                    key={server.id}
                    onClick={() => handleSelectServer(server)}
                    className="flex items-center justify-between p-3 bg-gray-50 rounded-lg cursor-pointer hover:bg-gray-100 transition-colors group"
                  >
                    <div>
                      <div className="font-medium text-gray-900">{server.name}</div>
                      <div className="text-sm text-gray-500">{server.url}</div>
                    </div>
                    <button
                      onClick={(e) => handleDeleteServer(e, server.id)}
                      className="p-2 text-gray-400 hover:text-red-600 opacity-0 group-hover:opacity-100 transition-opacity"
                    >
                      <Trash2 size={16} />
                    </button>
                  </div>
                ))}
              </div>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
