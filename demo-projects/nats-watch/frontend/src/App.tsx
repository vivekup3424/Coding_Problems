import { useState, useEffect } from 'react';
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { fetchServers } from './services/api';
import type { Server } from './types';
import Layout from './components/Layout';
import ConnectionPage from './pages/ConnectionPage';
import DashboardPage from './pages/DashboardPage';
import ClientsPage from './pages/ClientsPage';
import SubscriptionsPage from './pages/SubscriptionsPage';
import SettingsPage from './pages/SettingsPage';

function App() {
  const [servers, setServers] = useState<Server[]>([]);
  const [activeServer, setActiveServer] = useState<Server | null>(null);
  const [loading, setLoading] = useState(true);

  const loadServers = async () => {
    try {
      const data = await fetchServers();
      setServers(data);
      const active = data.find(s => s.is_active);
      setActiveServer(active || null);
    } catch (e) {
      console.error('Failed to load servers:', e);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    loadServers();
  }, []);

  if (loading) {
    return (
      <div className="min-h-screen flex items-center justify-center bg-gray-50">
        <div className="text-lg text-gray-600">Loading...</div>
      </div>
    );
  }

  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/connect"
          element={
            <ConnectionPage
              servers={servers}
              onServersChange={loadServers}
            />
          }
        />
        <Route
          path="/*"
          element={
            activeServer ? (
              <Layout server={activeServer} onDisconnect={() => { setActiveServer(null); loadServers(); }}>
                <Routes>
                  <Route path="/" element={<DashboardPage />} />
                  <Route path="/clients" element={<ClientsPage server={activeServer} />} />
                  <Route path="/subscriptions" element={<SubscriptionsPage />} />
                  <Route path="/settings" element={<SettingsPage server={activeServer} onUpdate={loadServers} />} />
                </Routes>
              </Layout>
            ) : (
              <Navigate to="/connect" replace />
            )
          }
        />
      </Routes>
    </BrowserRouter>
  );
}

export default App;
