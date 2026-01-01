import express from 'express';
import { WebSocketServer } from 'ws';
import { createServer } from 'http';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const server = createServer(app);
const wss = new WebSocketServer({ server });

app.use(express.static(path.join(__dirname, '../public')));
app.use(express.json());

const clients = new Set<any>();

wss.on('connection', (ws) => {
  console.log('Client connected to UI');
  clients.add(ws);

  ws.on('close', () => {
    console.log('Client disconnected from UI');
    clients.delete(ws);
  });
});

app.post('/api/events', (req, res) => {
  const event = req.body;
  console.log('Broadcasting event to UI clients:', event);
  
  clients.forEach((client) => {
    if (client.readyState === 1) {
      client.send(JSON.stringify(event));
    }
  });

  res.json({ success: true });
});

const PORT = process.env.UI_PORT || 8080;
server.listen(PORT, () => {
  console.log(`UI Server running on http://localhost:${PORT}`);
  console.log(`WebSocket server ready for connections`);
});
