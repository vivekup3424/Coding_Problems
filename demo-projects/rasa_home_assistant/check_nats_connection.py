#!/usr/bin/env python3
import socket
import json
import asyncio

host = "10.1.4.238"
port = 9769
site_id = "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0"


async def send_nats_message():
    """Send message to NATS topic"""
    try:
        import nats

        # Connect to NATS with token
        nc = await nats.connect(f"nats://keus-iot-platform@{host}:{port}")

        # Define topic and message
        topic = f"{site_id}-KIOTP-RPC"
        message = {
            "action": "EXECUTE_SCENE",
            "data": {
                "sceneId": "151",  # Replace with actual sceneId
                "sceneRoom": "Home"     # Replace with actual sceneRoom
            }
        }

        # Publish message
        await nc.publish(topic, json.dumps(message).encode())
        print(f"✅ Message sent to topic: {topic}")
        print(f"   Message: {json.dumps(message, indent=2)}")

        await nc.close()

    except ImportError:
        print("❌ nats-py library required. Install with: pip install nats-py")
    except Exception as e:
        print(f"❌ Failed to send message: {e}")


async def main():
    # Test TCP connection
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)
        result = sock.connect_ex((host, port))
        sock.close()

        if result == 0:
            print(f"✅ TCP connection to {host}:{port} successful")
        else:
            print(f"❌ TCP connection to {host}:{port} failed")
            return
    except Exception as e:
        print(f"❌ Connection error: {e}")
        return

    # Test NATS protocol and send message
    try:
        await send_nats_message()
    except Exception as e:
        print(f"❌ NATS operations failed: {e}")

# Run the async function
if __name__ == "__main__":
    asyncio.run(main())
