import { Client } from "@modelcontextprotocol/sdk/client/index.js";
import { StdioClientTransport } from "@modelcontextprotocol/sdk/client/stdio.js";
import { Ollama, type Message, type Tool } from "ollama";
import readline from "readline/promises";

async function main() {
  // Create transport and client
  const transport = new StdioClientTransport({
    command: "node",
    args: ["/root/Coding_Problems/mcpPractice/first/out.js"]
  });

  const client = new Client({
    name: "example-client",
    version: "1.0.0"
  });

  // Setup readline interface
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  // Setup Ollama client
  const ollama = new Ollama({ host: "http://172.24.128.1:11434" });
  
  try {
    // Connect to MCP server
    await client.connect(transport);
    console.log("Connected to MCP server successfully");

    // Get available tools
    const availableTools = await client.listTools();
    const tools = availableTools.tools.map(tool => ({
      type: "function",
      function: {
        name: tool.name,
        description: tool.description || "",
        parameters: tool.inputSchema,
      }
    } as Tool));

    const messages: Message[] = [];
    
    // Main chat loop
    while (true) {
      const userInput = await rl.question("\nYou: ");
      
      if (userInput.toLowerCase() === 'exit') {
        break;
      }

      // Add user message to history
      messages.push({ role: "user", content: userInput });
      
      try {
        // Get response from Ollama
        const response = await ollama.chat({
          model: "qwen2.5:7b",
          messages: [
            {
              role: "system",
              content: "verify and translate the context to english if you detect any other language"
            },
            ...messages
          ],
          stream: false,
          tools: tools
        });

        const assistantMessage = response.message;
        messages.push(assistantMessage);

        console.log("\nAssistant:", assistantMessage.content);

        // Handle tool calls if present
        if (assistantMessage.tool_calls) {
          for (const toolCall of assistantMessage.tool_calls) {
            try {
              const toolArgs = toolCall.function.arguments;
              const result = await client.callTool({
                name: toolCall.function.name,
                arguments: toolArgs
              });

              // Add tool response to message history
              messages.push({
                role: "tool",
                content: JSON.stringify(result)
              });

              console.log(`\nTool ${toolCall.function.name} result:`, result);
            } catch (error) {
              const errorMessage = error instanceof Error ? error.message : 'Unknown error';
              console.error(`Error calling tool ${toolCall.function.name}:`, errorMessage);
              
              messages.push({
                role: "tool",
                content: JSON.stringify({ error: errorMessage })
              });
            }
          }
        }
      } catch (error) {
        const errorMessage = error instanceof Error ? error.message : 'Unknown error';
        console.error("Error in chat loop:", errorMessage);
      }
    }
  } catch (error) {
    const errorMessage = error instanceof Error ? error.message : 'Unknown error';
    console.error("Error:", errorMessage);
  } finally {
    // Clean up resources
    rl.close();
    await client.close().catch(console.error);
    await transport.close().catch(console.error);
    console.log("\nChat session ended. Goodbye!");
  }
}

// Handle process termination
process.on('SIGINT', () => {
  console.log("\nReceived SIGINT. Cleaning up...");
  process.exit(0);
});

process.on('SIGTERM', () => {
  console.log("\nReceived SIGTERM. Cleaning up...");
  process.exit(0);
});

main().catch((error) => {
  console.error("Unhandled error:", error instanceof Error ? error.message : error);
  process.exit(1);
});