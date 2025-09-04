import WebSocket, { WebSocketServer } from "ws";

const wss = new WebSocketServer({ port: 8080 });

wss.on("connection", (ws) => {
  console.log("Client connected");

  ws.on("message", (message) => {
    try {
      const msgObj = message;
      console.log(message);
      // console.log(`Received from ${msgObj.user}: ${msgObj.text}`);
      wss.clients.forEach(client => {
        if (client != ws && client.readyState === WebSocket.OPEN) {
          client.send(JSON.stringify(msgObj));
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