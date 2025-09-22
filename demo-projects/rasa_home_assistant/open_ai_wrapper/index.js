const express = require("express");
const cors = require("cors");
const axios = require("axios");

const app = express();
const router = express.Router();

// Configuration
const RASA_SERVER_URL = process.env.RASA_SERVER_URL || 'http://localhost:5005';
const WRAPPER_PORT = process.env.WRAPPER_PORT || 8881;

app.use(cors());
app.use(express.json());

// Helper function to convert OpenAI chat messages to Rasa format
function convertToRasaMessage(openAiMessages) {
  // Get the last user message (most recent)
  const lastUserMessage = openAiMessages
    .filter(msg => msg.role === 'user')
    .pop();
  
  return {
    message: lastUserMessage?.content || '',
    sender: 'user'
  };
}

// Helper function to convert Rasa response to OpenAI format
function convertToOpenAiResponse(rasaResponse, isStreaming = false, model = 'rasa-model') {
  const response = rasaResponse[0]; // Rasa returns array of responses
  const content = response?.text || 'I apologize, but I could not process your request.';
  
  const timestamp = Math.floor(Date.now() / 1000);
  const completionId = `chatcmpl-rasa-${timestamp}`;
  
  if (isStreaming) {
    return {
      id: completionId,
      object: "chat.completion.chunk",
      created: timestamp,
      model: model,
      choices: [{
        delta: { content: content },
        index: 0,
        finish_reason: null,
      }],
    };
  } else {
    return {
      id: completionId,
      object: "chat.completion",
      created: timestamp,
      model: model,
      choices: [{
        index: 0,
        message: {
          role: "assistant",
          content: content,
        },
        finish_reason: "stop",
      }],
      usage: {
        prompt_tokens: content.split(' ').length * 2, // Rough estimate
        completion_tokens: content.split(' ').length,
        total_tokens: content.split(' ').length * 3,
      },
    };
  }
}

router.post("/chat/completions", async (req, res) => {
  try {
    const { stream, messages, model } = req.body;
    
    // Convert OpenAI messages to Rasa format
    const rasaMessage = convertToRasaMessage(messages || []);
    
    console.log(`[${new Date().toISOString()}] Forwarding to Rasa: "${rasaMessage.message}"`);
    
    // Send request to Rasa server
    const rasaResponse = await axios.post(`${RASA_SERVER_URL}/webhooks/rest/webhook`, rasaMessage, {
      timeout: 10000, // 10 second timeout
      headers: {
        'Content-Type': 'application/json'
      }
    });
    
    if (!rasaResponse.data || !Array.isArray(rasaResponse.data)) {
      throw new Error('Invalid response from Rasa server');
    }
    
    console.log(`[${new Date().toISOString()}] Rasa response:`, rasaResponse.data);
    
    // Handle non-streaming response
    if (!stream) {
      const openAiResponse = convertToOpenAiResponse(rasaResponse.data, false, model);
      return res.json(openAiResponse);
    }
    
    // Handle streaming response
    res.setHeader("Content-Type", "text/event-stream");
    res.setHeader("Cache-Control", "no-cache");
    res.setHeader("Connection", "keep-alive");
    res.setHeader("Transfer-Encoding", "chunked");
    
    // For streaming, we'll simulate word-by-word streaming of the Rasa response
    const response = rasaResponse.data[0];
    const content = response?.text || 'I apologize, but I could not process your request.';
    const words = content.split(" ");
    
    let index = 0;
    const completionId = `chatcmpl-rasa-${Math.floor(Date.now() / 1000)}`;
    
    const sendChunk = () => {
      if (index < words.length) {
        const chunk = {
          id: completionId,
          object: "chat.completion.chunk",
          created: Math.floor(Date.now() / 1000),
          model: model || "rasa-model",
          choices: [{
            delta: { content: words[index] + " " },
            index: 0,
            finish_reason: null,
          }],
        };
        
        res.write(`data: ${JSON.stringify(chunk)}\n\n`);
        index++;
        setTimeout(sendChunk, 100); // Faster streaming than original
      } else {
        // Send final chunk to indicate completion
        const finalChunk = {
          id: completionId,
          object: "chat.completion.chunk",
          created: Math.floor(Date.now() / 1000),
          model: model || "rasa-model",
          choices: [{
            delta: {},
            index: 0,
            finish_reason: "stop",
          }],
        };
        res.write(`data: ${JSON.stringify(finalChunk)}\n\n`);
        res.write(`data: [DONE]\n\n`);
        res.end();
      }
    };
    
    sendChunk();
    
  } catch (error) {
    console.error(`[${new Date().toISOString()}] Error:`, error.message);
    
    // Handle errors gracefully
    const errorResponse = {
      id: `chatcmpl-error-${Math.floor(Date.now() / 1000)}`,
      object: "chat.completion",
      created: Math.floor(Date.now() / 1000),
      model: req.body.model || "rasa-model",
      choices: [{
        index: 0,
        message: {
          role: "assistant",
          content: "I'm sorry, I'm having trouble connecting to the assistant right now. Please try again in a moment.",
        },
        finish_reason: "stop",
      }],
      usage: {
        prompt_tokens: 10,
        completion_tokens: 20,
        total_tokens: 30,
      },
    };
    
    if (req.body.stream) {
      // If it was a streaming request, set appropriate headers and send error as stream
      if (!res.headersSent) {
        res.setHeader("Content-Type", "text/event-stream");
        res.setHeader("Cache-Control", "no-cache");
        res.setHeader("Connection", "keep-alive");
      }
      res.write(`data: ${JSON.stringify({
        ...errorResponse,
        object: "chat.completion.chunk",
        choices: [{
          delta: { content: errorResponse.choices[0].message.content },
          index: 0,
          finish_reason: "stop",
        }]
      })}\n\n`);
      res.write(`data: [DONE]\n\n`);
      res.end();
    } else {
      res.status(500).json(errorResponse);
    }
  }
});
// Mount the router
app.use('/', router);

// Health check endpoint
app.get('/health', (req, res) => {
  res.json({ 
    status: 'healthy', 
    timestamp: new Date().toISOString(),
    rasaServer: RASA_SERVER_URL,
    port: WRAPPER_PORT
  });
});

// Start server
app.listen(WRAPPER_PORT, () => {
  console.log(`🚀 LiveKit-Rasa Wrapper running on http://localhost:${WRAPPER_PORT}`);
  console.log(`📡 Forwarding requests to Rasa server at: ${RASA_SERVER_URL}`);
  console.log(`🏥 Health check available at: http://localhost:${WRAPPER_PORT}/health`);
  console.log(`💬 Chat completions endpoint: http://localhost:${WRAPPER_PORT}/chat/completions`);
});