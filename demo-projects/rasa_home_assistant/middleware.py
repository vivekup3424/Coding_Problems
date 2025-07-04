#!/usr/bin/env python3
"""
Rasa API Middleware - Intercepts and transforms requests/responses
Requires minimal changes: just run this alongside your existing Rasa server
"""

from flask import Flask, request, jsonify, Response
from flask_cors import CORS
import requests
import json
import logging
import time
import uuid
import ssl
from typing import Dict, Any, List

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = Flask(__name__)

# Enable CORS for all routes and origins
CORS(app, resources={
    r"/*": {
        "origins": "*",
        "methods": ["GET", "POST", "PUT", "DELETE", "OPTIONS"],
        "allow_headers": ["Content-Type", "Authorization", "Accept", "Origin", "X-Requested-With"]
    }
})

# Configuration
RASA_URL = "http://localhost:5005"
MIDDLEWARE_PORT = 8000
HTTPS_ENABLED = True  # Set to True to enable HTTPS
SSL_CERT_PATH = "cert.pem"  # Path to SSL certificate
SSL_KEY_PATH = "key.pem"   # Path to SSL private key


class RequestTransformer:
    """Transform incoming requests to Rasa format"""

    @staticmethod
    def transform_request(data: Dict[str, Any]) -> Dict[str, Any]:
        """
        Transform OpenAI/LLaMA chat format to Rasa webhook format

        Input:  {
            "model": "llama2",
            "messages": [
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": "Hello!"}
            ]
        }

        Output: {"sender": "user", "message": "Hello!"}
        """
        logger.info(f"Original request: {data}")

        # Validate that this is OpenAI/LLaMA chat format
        if "messages" not in data or not isinstance(data["messages"], list):
            raise ValueError(
                "Invalid request format. Expected 'messages' array.")

        # Find the last user message
        user_message = ""
        for message in reversed(data["messages"]):
            if message.get("role") == "user":
                user_message = message.get("content", "")
                break

        if not user_message:
            raise ValueError("No user message found in the request.")

        transformed = {
            "sender": "user",
            "message": user_message
        }

        # Add model info as metadata if present
        if "model" in data:
            transformed["metadata"] = {"model": data["model"]}

        logger.info(f"Transformed request: {transformed}")
        return transformed


class ResponseTransformer:
    """Transform Rasa responses to OpenAI chat completion format"""

    @staticmethod
    def transform_response(rasa_response: List[Dict[str, Any]], completion_id: str, model: str, created_timestamp: int) -> Dict[str, Any]:
        """
        Transform Rasa response to OpenAI chat completion format

        Input:  [{"text": "Hello!"}, {"image": "url"}]
        Output: OpenAI chat completion format
        """
        logger.info(f"Original Rasa response: {rasa_response}")

        # Extract text responses from Rasa
        text_responses = []
        for resp in rasa_response:
            if "text" in resp:
                text_responses.append(resp["text"])

        # Combine all text responses
        reply = " ".join(
            text_responses) if text_responses else "I understand, but I don't have a response for that."

        transformed = {
            "id": completion_id,
            "object": "chat.completion",
            "created": created_timestamp,
            "model": model,
            "choices": [
                {
                    "index": 0,
                    "message": {
                        "role": "assistant",
                        "content": reply,
                    },
                    "finish_reason": "stop",
                },
            ],
            "usage": {
                "prompt_tokens": 10,  # Rough estimate
                "completion_tokens": len(reply.split()),
                "total_tokens": 10 + len(reply.split()),
            },
        }

        logger.info(f"Transformed response: {transformed}")
        return transformed


@app.route('/chat/completions', methods=['POST'])
def chat_completions():
    """OpenAI-compatible chat completions endpoint with streaming support"""
    try:
        if not request.json:
            return jsonify({"error": "No JSON data provided"}), 400

        request_data = request.json
        stream = request_data.get("stream", False)
        model = request_data.get("model", "rasa-model")

        transformer = RequestTransformer()
        transformed_request = transformer.transform_request(request_data)

        rasa_endpoint = f"{RASA_URL}/webhooks/rest/webhook"
        logger.info(f"Forwarding to: {rasa_endpoint}")

        response = requests.post(
            rasa_endpoint,
            json=transformed_request,
            headers={'Content-Type': 'application/json'},
            timeout=30
        )

        if response.status_code != 200:
            logger.error(
                f"Rasa returned error: {response.status_code} - {response.text}")
            return jsonify({"error": "Rasa server error", "details": response.text}), response.status_code

        rasa_data = response.json()

        completion_id = f"chatcmpl-{uuid.uuid4().hex[:12]}"
        created_timestamp = int(time.time())

        if not stream:
            response_transformer = ResponseTransformer()
            openai_response = response_transformer.transform_response(
                rasa_data, completion_id, model, created_timestamp
            )
            return jsonify(openai_response)

        # Streaming response (Server-Sent Events)
        # Extract text responses from Rasa for streaming
        text_responses = []
        for resp in rasa_data:
            if "text" in resp:
                text_responses.append(resp["text"])

        # Combine all text responses
        reply = " ".join(
            text_responses) if text_responses else "I understand, but I don't have a response for that."

        # Streaming response (Server-Sent Events)
        def generate_stream():
            words = reply.split(" ")

            for index, word in enumerate(words):
                chunk = {
                    "id": completion_id,
                    "object": "chat.completion.chunk",
                    "created": created_timestamp,
                    "model": model,
                    "choices": [
                        {
                            "delta": {"content": word + (" " if index < len(words) - 1 else "")},
                            "index": 0,
                            "finish_reason": None,
                        },
                    ],
                }

                yield f"data: {json.dumps(chunk)}\n\n"
                time.sleep(0.1)  # Simulate token delay

            # Send final chunk to indicate completion
            final_chunk = {
                "id": completion_id,
                "object": "chat.completion.chunk",
                "created": created_timestamp,
                "model": model,
                "choices": [
                    {
                        "delta": {},
                        "index": 0,
                        "finish_reason": "stop",
                    },
                ],
            }
            yield f"data: {json.dumps(final_chunk)}\n\n"
            yield "data: [DONE]\n\n"

        return Response(
            generate_stream(),
            mimetype='text/event-stream',
            headers={
                'Cache-Control': 'no-cache',
                'Transfer-Encoding': 'chunked'
            }
        )

    except ValueError as e:
        logger.error(f"Request validation error: {e}")
        return jsonify({"error": str(e)}), 400
    except requests.RequestException as e:
        logger.error(f"Request to Rasa failed: {e}")
        return jsonify({"error": "Failed to connect to Rasa server"}), 503
    except Exception as e:
        logger.error(f"Unexpected error: {e}")
        return jsonify({"error": "Internal server error"}), 500


@app.route('/', methods=['GET'])
def health_check():
    """Health check endpoint"""
    return jsonify({"status": "ok"}), 200


if __name__ == '__main__':
    print(f"""
    🚀 Rasa API Middleware Starting...
    
    Middleware URL: {'https' if HTTPS_ENABLED else 'http'}://localhost:{MIDDLEWARE_PORT}
    Rasa URL: {RASA_URL}
    HTTPS Enabled: {HTTPS_ENABLED}
    CORS Enabled: True (All origins allowed)

    Endpoints:
    - POST /chat/completions (OpenAI-compatible chat completions with streaming)
    - GET / (Health check)
    
    To test streaming:
    curl -X POST {'https' if HTTPS_ENABLED else 'http'}://localhost:{MIDDLEWARE_PORT}/chat/completions \\
         -H "Content-Type: application/json" \\
         -d '{{
             "model": "rasa-model",
             "stream": true,
             "messages": [
                 {{"role": "system", "content": "You are a helpful assistant."}},
                 {{"role": "user", "content": "Hello!"}}
             ]
         }}'
    """)

    if HTTPS_ENABLED:
        # Create SSL context
        try:
            context = ssl.SSLContext(ssl.PROTOCOL_TLSv1_2)
            context.load_cert_chain(SSL_CERT_PATH, SSL_KEY_PATH)
            print(
                f"✅ SSL certificates loaded from {SSL_CERT_PATH} and {SSL_KEY_PATH}")
            app.run(host='0.0.0.0', port=MIDDLEWARE_PORT,
                    debug=True, ssl_context=context)
        except FileNotFoundError as e:
            print(f"❌ SSL certificate files not found: {e}")
            print("💡 To generate self-signed certificates, run:")
            print(
                f"   openssl req -x509 -newkey rsa:4096 -nodes -out {SSL_CERT_PATH} -keyout {SSL_KEY_PATH} -days 365")
            print("   Or set HTTPS_ENABLED = False to use HTTP")
        except Exception as e:
            print(f"❌ SSL setup failed: {e}")
            print("   Falling back to HTTP mode...")
            app.run(host='0.0.0.0', port=MIDDLEWARE_PORT, debug=True)
    else:
        app.run(host='0.0.0.0', port=MIDDLEWARE_PORT, debug=True)
