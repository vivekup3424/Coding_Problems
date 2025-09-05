import WebSocket, { WebSocketServer } from "ws";

const wss = new WebSocketServer({ port: 8080 });

wss.on("connection", (ws) => {
  console.log("Client connected");

  ws.on("message", (message) => {
    try {
      const messageObject = JSON.parse(message.toString());
      console.log(messageObject);
      wss.clients.forEach(client => {
        if (client != ws && client.readyState === WebSocket.OPEN) {
          client.send(JSON.stringify(messageObject));
        }
      });
    } catch (err) {
      console.error("Invalid message format", err);
    }
  });

  ws.on("error", (err) => {
    console.error("WebSocket error:", err);
  });
});