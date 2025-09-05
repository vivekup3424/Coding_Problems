const ws = new WebSocket('ws://localhost:8080');
const textArea = document.getElementById('editor');
ws.onopen = () => {
    console.log('Connected to WebSocket server');
}
ws.onmessage = (event)=>{
    console.log('Message from server ', event.data);
    const msg = JSON.parse(event.data);
    textArea.innerText = msg.content;
}
 textArea.addEventListener('input', (event)=>{
   ws.send(JSON.stringify({ type: 'input', content: event.target.innerText }));
 })