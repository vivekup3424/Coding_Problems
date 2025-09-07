const ws = new WebSocket('ws://192.168.1.41:8080');
const textArea = document.getElementById('editor');
ws.onopen = () => {
    console.log('Connected to WebSocket server');
}
ws.onmessage = (event)=>{
    console.log('Message from server ', event.data);
    const msg = JSON.parse(event.data);
    textArea.innerText = msg.content;
    if(msg.cursor){
      const range = document.createRange();
      const selection = window.getSelection();
      range.setStart(textArea.childNodes[0] || textArea, msg.cursor.start);
      range.setEnd(textArea.childNodes[0] || textArea, msg.cursor.end);
      selection.removeAllRanges();
      selection.addRange(range);
    }
}
 textArea.addEventListener('input', (event)=>{
  const cursorPos = getCursorPosition();
   ws.send(JSON.stringify({ type: 'input', content: event.target.innerText, cursor: cursorPos }));
 })


function getCursorPosition(){
  const selection = window.getSelection();
  if(!selection || selection.rangeCount === 0) return null;
  const range = selection.getRangeAt(0);
  return {start: range.startOffset, end: range.endOffset};
}