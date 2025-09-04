import WebSocket from 'ws';
import readline from 'readline';

const ws = new WebSocket('ws://localhost:8080');
const user = crypto.randomUUID().substring(0, 8); // You can make this dynamic

ws.on('error', console.error);

ws.on('open', function open() {
    const data = { user, text: "Hello, WebSocket!" };
    ws.send(JSON.stringify(data));
});

ws.on('message', function message(data) {
    try {
        const msgObj = JSON.parse(data.toString());
        console.log(`[${msgObj.user}]: ${msgObj.text}`);
    } catch {
        console.log('Received:', data.toString());
    }
});

const read1 = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const questLine = () => {
    read1.question("Enter message: ", (msg) => {
        ws.send(JSON.stringify({ user, text: msg }));
        questLine();
    });
};

process.on('SIGINT', () => {
    console.log("\nDisconnecting...");
    ws.close();
    read1.close();
    process.exit();
});

questLine();