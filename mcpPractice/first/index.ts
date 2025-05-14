import Moleculer from "moleculer";
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js";
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";
import { z } from "zod";

(async () => {
  try {
    const response = await fetch("http://172.24.128.1:3000/keus/v1/node_configuration/GetNodeConfig");
    if (!response.ok) {
      throw new Error(`Failed to fetch node configuration: ${response.statusText}`);
    }
    const data = await response.json();
    const siteId = data.nodeConfig.siteInfo.siteId;

    const moleculerServer = new Moleculer.ServiceBroker({
      namespace: siteId,
      nodeID: crypto.randomUUID(),
      transporter: {
        type: "NATS",
        options: {
          url: "nats://172.24.128.1:9769",
          token: 'keus-iot-platform',
        }
      },
      logger: {
        type: "Console",
        options: {
          level: "info"
        }
      }
    });

    await moleculerServer.start();

    // Initialize MCP server
    const server = new McpServer({
      name: "example-server",
      version: "1.0.0"
    },
    {
      capabilities: {
        tools: {},
        resources: {}
      }
    });

    // Register tools
    server.tool(
      "GetAllService",
      "Get the details of all services available on keus-iot-platform",
      {
        query: z.string()
      },
      async (args) => {
        try {
          const services = await moleculerServer.call("$node.services");
          return {
            content: [{
              type: "text",
              text: JSON.stringify(services, null, 2)
            }]
          };
        } catch (error: unknown) {
          console.error("Error fetching services:", error);
          const errorMessage = error instanceof Error ? error.message : 'Unknown error occurred';
          return {
            content: [{
              type: "text",
              text: `Error fetching services: ${errorMessage}`
            }],
            isError: true
          };
        }
      }
    );

    server.tool(
      "GetAllActions",
      "Get the details of all actions available on keus-iot-platform",
      {
        query: z.string()
      },
      async (args) => {
        try {
          const actions = await moleculerServer.call("$node.actions");
          return {
            content: [{
              type: "text",
              text: JSON.stringify(actions, null, 2)
            }]
          };
        } catch (error: unknown) {
          console.error("Error fetching actions:", error);
          const errorMessage = error instanceof Error ? error.message : 'Unknown error occurred';
          return {
            content: [{
              type: "text",
              text: `Error fetching actions: ${errorMessage}`
            }],
            isError: true
          };
        }
      }
    );

    const transport = new StdioServerTransport();
    await server.connect(transport);
    console.log("MCP server connected successfully");

    const shutdown = async () => {
      console.log("Shutting down servers...");
      await moleculerServer.stop();
      await server.close();
      console.log("Servers stopped successfully");
      process.exit(0);
    };

    process.on('SIGINT', shutdown);
    process.on('SIGTERM', shutdown);

  } catch (error) {
    console.error("Fatal error:", error);
    process.exit(1);
  }
})();