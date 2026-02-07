import { useEffect, useRef, useState, useCallback } from 'react';
import type { VarzData, ConnzData, SubzData, WSMessage } from '../types';

interface UseWebSocketReturn {
  varz: VarzData | null;
  connz: ConnzData | null;
  subz: SubzData | null;
  connected: boolean;
  error: string | null;
}

export function useWebSocket(enabled: boolean): UseWebSocketReturn {
  const [varz, setVarz] = useState<VarzData | null>(null);
  const [connz, setConnz] = useState<ConnzData | null>(null);
  const [subz, setSubz] = useState<SubzData | null>(null);
  const [connected, setConnected] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const wsRef = useRef<WebSocket | null>(null);
  const reconnectTimeoutRef = useRef<number | null>(null);

  const connect = useCallback(() => {
    if (!enabled) return;

    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const wsUrl = `${protocol}//${window.location.host}/ws/metrics`;

    try {
      const ws = new WebSocket(wsUrl);
      wsRef.current = ws;

      ws.onopen = () => {
        setConnected(true);
        setError(null);
      };

      ws.onmessage = (event) => {
        try {
          const msg: WSMessage = JSON.parse(event.data);
          switch (msg.type) {
            case 'varz':
              setVarz(msg.data as VarzData);
              break;
            case 'connz':
              setConnz(msg.data as ConnzData);
              break;
            case 'subz':
              setSubz(msg.data as SubzData);
              break;
          }
        } catch (e) {
          console.error('Failed to parse WebSocket message:', e);
        }
      };

      ws.onerror = () => {
        setError('WebSocket connection error');
      };

      ws.onclose = () => {
        setConnected(false);
        wsRef.current = null;

        // Reconnect after 5 seconds
        if (enabled) {
          reconnectTimeoutRef.current = window.setTimeout(() => {
            connect();
          }, 5000);
        }
      };
    } catch (e) {
      setError('Failed to create WebSocket connection');
    }
  }, [enabled]);

  useEffect(() => {
    connect();

    return () => {
      if (wsRef.current) {
        wsRef.current.close();
      }
      if (reconnectTimeoutRef.current) {
        clearTimeout(reconnectTimeoutRef.current);
      }
    };
  }, [connect]);

  return { varz, connz, subz, connected, error };
}
