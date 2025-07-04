# Using Rasa Server Through Middleware Proxy

## Overview

This middleware acts as a **proxy** between clients and your Rasa server, providing:
- 🔌 **OpenAI-compatible API** (`/chat/completions`)
- 🌊 **Streaming support** for real-time responses
- 🌐 **CORS enabled** for web applications
- 🔒 **HTTPS support** for secure connections
- 📝 **Request/Response transformation** (OpenAI format ↔ Rasa format)

## Architecture

```
Client → Middleware Proxy (Port 8000) → Rasa Server (Port 5005)
```

The middleware:
1. Receives OpenAI-format requests
2. Transforms them to Rasa webhook format
3. Forwards to your Rasa server
4. Transforms Rasa responses back to OpenAI format
5. Returns streaming or non-streaming responses

## API Endpoint

**Base URL:** `http://localhost:8000` (or `https://localhost:8000` if HTTPS enabled)

**Endpoint:** `POST /chat/completions`

## Request Format

### OpenAI-Compatible Format
```json
{
  "model": "rasa-model",
  "stream": false,
  "messages": [
    {
      "role": "system",
      "content": "You are a helpful home assistant."
    },
    {
      "role": "user", 
      "content": "Turn on the living room lights"
    }
  ]
}
```

### Parameters
- `model`: Model name (optional, defaults to "rasa-model")
- `stream`: Boolean - Enable streaming response (default: false)
- `messages`: Array of message objects with `role` and `content`

## Response Format

### Non-Streaming Response
```json
{
  "id": "chatcmpl-abc123",
  "object": "chat.completion",
  "created": 1672531200,
  "model": "rasa-model",
  "choices": [
    {
      "index": 0,
      "message": {
        "role": "assistant",
        "content": "I'll turn on the living room lights for you!"
      },
      "finish_reason": "stop"
    }
  ],
  "usage": {
    "prompt_tokens": 10,
    "completion_tokens": 8,
    "total_tokens": 18
  }
}
```

### Streaming Response (Server-Sent Events)
```
data: {"id":"chatcmpl-abc123","object":"chat.completion.chunk","created":1672531200,"model":"rasa-model","choices":[{"delta":{"content":"I'll "},"index":0,"finish_reason":null}]}

data: {"id":"chatcmpl-abc123","object":"chat.completion.chunk","created":1672531200,"model":"rasa-model","choices":[{"delta":{"content":"turn "},"index":0,"finish_reason":null}]}

data: {"id":"chatcmpl-abc123","object":"chat.completion.chunk","created":1672531200,"model":"rasa-model","choices":[{"delta":{},"index":0,"finish_reason":"stop"}]}

data: [DONE]
```

## Client Examples

### 1. curl (Command Line)

**Non-streaming:**
```bash
curl -X POST http://localhost:8000/chat/completions \
     -H "Content-Type: application/json" \
     -d '{
       "model": "rasa-model",
       "stream": false,
       "messages": [
         {"role": "system", "content": "You are a helpful assistant."},
         {"role": "user", "content": "Hello!"}
       ]
     }'
```

**Streaming:**
```bash
curl -X POST http://localhost:8000/chat/completions \
     -H "Content-Type: application/json" \
     -d '{
       "model": "rasa-model", 
       "stream": true,
       "messages": [
         {"role": "user", "content": "Tell me a joke"}
       ]
     }'
```

### 2. Python Client

```python
import requests
import json

class RasaChatClient:
    def __init__(self, base_url="http://localhost:8000"):
        self.base_url = base_url
        self.session = requests.Session()
    
    def chat(self, message, stream=False, model="rasa-model"):
        """Send a chat message to Rasa via middleware"""
        url = f"{self.base_url}/chat/completions"
        
        payload = {
            "model": model,
            "stream": stream,
            "messages": [
                {"role": "user", "content": message}
            ]
        }
        
        if stream:
            return self._stream_chat(url, payload)
        else:
            response = self.session.post(url, json=payload)
            response.raise_for_status()
            return response.json()
    
    def _stream_chat(self, url, payload):
        """Handle streaming response"""
        response = self.session.post(url, json=payload, stream=True)
        response.raise_for_status()
        
        for line in response.iter_lines():
            if line:
                line_str = line.decode('utf-8')
                if line_str.startswith('data: '):
                    data = line_str[6:]
                    if data != '[DONE]':
                        try:
                            chunk = json.loads(data)
                            yield chunk
                        except json.JSONDecodeError:
                            pass

# Usage example
client = RasaChatClient()

# Non-streaming
response = client.chat("Turn on the lights")
print(response['choices'][0]['message']['content'])

# Streaming
for chunk in client.chat("Tell me about the weather", stream=True):
    if 'choices' in chunk and chunk['choices']:
        content = chunk['choices'][0].get('delta', {}).get('content', '')
        if content:
            print(content, end='', flush=True)
```

### 3. JavaScript/Web Client

```javascript
class RasaChatClient {
    constructor(baseUrl = 'http://localhost:8000') {
        this.baseUrl = baseUrl;
    }
    
    async chat(message, stream = false, model = 'rasa-model') {
        const url = `${this.baseUrl}/chat/completions`;
        
        const payload = {
            model: model,
            stream: stream,
            messages: [
                { role: 'user', content: message }
            ]
        };
        
        if (stream) {
            return this.streamChat(url, payload);
        } else {
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(payload)
            });
            
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
            return await response.json();
        }
    }
    
    async *streamChat(url, payload) {
        const response = await fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(payload)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const reader = response.body.getReader();
        const decoder = new TextDecoder();
        
        while (true) {
            const { done, value } = await reader.read();
            
            if (done) break;
            
            const chunk = decoder.decode(value);
            const lines = chunk.split('\n');
            
            for (const line of lines) {
                if (line.startsWith('data: ')) {
                    const data = line.slice(6);
                    if (data !== '[DONE]') {
                        try {
                            yield JSON.parse(data);
                        } catch (e) {
                            // Skip invalid JSON
                        }
                    }
                }
            }
        }
    }
}

// Usage example
const client = new RasaChatClient();

// Non-streaming
client.chat('Hello!')
    .then(response => {
        console.log(response.choices[0].message.content);
    });

// Streaming
async function streamExample() {
    for await (const chunk of client.streamChat('Tell me a story', true)) {
        if (chunk.choices && chunk.choices[0]) {
            const content = chunk.choices[0].delta?.content || '';
            if (content) {
                document.body.appendChild(document.createTextNode(content));
            }
        }
    }
}
```

### 4. Node.js Client

```javascript
const axios = require('axios');

class RasaChatClient {
    constructor(baseUrl = 'http://localhost:8000') {
        this.baseUrl = baseUrl;
    }
    
    async chat(message, stream = false, model = 'rasa-model') {
        const url = `${this.baseUrl}/chat/completions`;
        
        const payload = {
            model: model,
            stream: stream,
            messages: [
                { role: 'user', content: message }
            ]
        };
        
        if (stream) {
            return this.streamChat(url, payload);
        } else {
            const response = await axios.post(url, payload);
            return response.data;
        }
    }
    
    async *streamChat(url, payload) {
        const response = await axios({
            method: 'POST',
            url: url,
            data: payload,
            responseType: 'stream'
        });
        
        for await (const chunk of response.data) {
            const lines = chunk.toString().split('\n');
            
            for (const line of lines) {
                if (line.startsWith('data: ')) {
                    const data = line.slice(6);
                    if (data !== '[DONE]') {
                        try {
                            yield JSON.parse(data);
                        } catch (e) {
                            // Skip invalid JSON
                        }
                    }
                }
            }
        }
    }
}

// Usage
const client = new RasaChatClient();

// Non-streaming
client.chat('Hello!')
    .then(response => {
        console.log(response.choices[0].message.content);
    });
```

## Integration with Popular Libraries

### OpenAI Python SDK (Compatible)
```python
import openai

# Point to your middleware instead of OpenAI
client = openai.OpenAI(
    api_key="dummy-key",  # Not used by your middleware
    base_url="http://localhost:8000"
)

response = client.chat.completions.create(
    model="rasa-model",
    messages=[
        {"role": "user", "content": "Hello!"}
    ]
)

print(response.choices[0].message.content)
```

## Deployment for Public Access

### 1. Cloud Deployment (AWS/GCP/Azure)

```yaml
# docker-compose.yml
version: '3.8'
services:
  rasa-middleware:
    build: .
    ports:
      - "443:8000"  # HTTPS
      - "80:8000"   # HTTP redirect
    environment:
      - RASA_URL=http://rasa-server:5005
      - HTTPS_ENABLED=true
    volumes:
      - ./certs:/app/certs
    depends_on:
      - rasa-server
      
  rasa-server:
    image: rasa/rasa:latest
    ports:
      - "5005:5005"
    volumes:
      - ./rasa-project:/app
    command: run --enable-api --cors "*"
```

### 2. Domain Setup

1. **Get a domain:** `your-domain.com`
2. **Point to your server IP**
3. **Get SSL certificate:** Let's Encrypt
4. **Update middleware config:**
   ```python
   HTTPS_ENABLED = True
   SSL_CERT_PATH = "/etc/letsencrypt/live/your-domain.com/fullchain.pem"
   SSL_KEY_PATH = "/etc/letsencrypt/live/your-domain.com/privkey.pem"
   ```

### 3. Production CORS (Restrict Origins)

```python
CORS(app, resources={
    r"/*": {
        "origins": ["https://yourdomain.com", "https://app.yourdomain.com"],
        "methods": ["POST", "OPTIONS"],
        "allow_headers": ["Content-Type", "Authorization"]
    }
})
```

## Usage Examples for Different Scenarios

### 1. Chatbot Widget
```html
<!-- Embed in any website -->
<div id="chatbot"></div>
<script>
const client = new RasaChatClient('https://your-domain.com');

async function sendMessage(message) {
    const response = await client.chat(message);
    document.getElementById('chatbot').innerHTML += 
        `<p><strong>Bot:</strong> ${response.choices[0].message.content}</p>`;
}
</script>
```

### 2. Mobile App Integration
```swift
// iOS Swift example
func sendMessage(message: String) {
    let url = URL(string: "https://your-domain.com/chat/completions")!
    var request = URLRequest(url: url)
    request.httpMethod = "POST"
    request.setValue("application/json", forHTTPHeaderField: "Content-Type")
    
    let payload = [
        "model": "rasa-model",
        "messages": [
            ["role": "user", "content": message]
        ]
    ]
    
    request.httpBody = try! JSONSerialization.data(withJSONObject: payload)
    
    URLSession.shared.dataTask(with: request) { data, response, error in
        // Handle response
    }.resume()
}
```

### 3. Slack Bot Integration
```python
from slack_bolt import App

app = App(token="your-slack-token")
client = RasaChatClient("https://your-domain.com")

@app.message(".*")
def handle_message(message, say):
    response = client.chat(message['text'])
    say(response['choices'][0]['message']['content'])
```

## Security Considerations

1. **Rate Limiting:** Implement rate limiting to prevent abuse
2. **Authentication:** Add API key authentication if needed
3. **HTTPS Only:** Force HTTPS in production
4. **CORS:** Restrict origins to trusted domains
5. **Firewall:** Only expose necessary ports

## Monitoring and Logging

The middleware logs all requests and responses. Monitor:
- Request volume
- Response times
- Error rates
- Rasa server health

This setup allows anyone to integrate with your Rasa server using the familiar OpenAI API format!
