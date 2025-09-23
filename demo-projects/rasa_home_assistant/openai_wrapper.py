#!/usr/bin/env python3
"""OpenAI-compatible wrapper for Rasa Assistant"""

import os
import json
import time
import asyncio
from datetime import datetime
from typing import List, Dict, Any, Optional

import aiohttp
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import StreamingResponse
from pydantic import BaseModel
import uvicorn

# Configuration
RASA_SERVER_URL = os.getenv('RASA_SERVER_URL', 'http://localhost:5005')
WRAPPER_PORT = int(os.getenv('WRAPPER_PORT', '8881'))

# Models
class ChatMessage(BaseModel):
    role: str
    content: str

class ChatCompletionRequest(BaseModel):
    messages: List[ChatMessage]
    model: Optional[str] = "rasa-model"
    stream: Optional[bool] = False

# App setup
app = FastAPI()
app.add_middleware(CORSMiddleware, allow_origins=["*"], allow_methods=["*"], allow_headers=["*"])

def convert_to_rasa_message(messages: List[ChatMessage]) -> Dict[str, str]:
    user_messages = [msg for msg in messages if msg.role == 'user']
    last_message = user_messages[-1] if user_messages else None
    return {"message": last_message.content if last_message else '', "sender": "user"}

def convert_to_openai_response(rasa_response: List[Dict], model: str) -> Dict:
    content = rasa_response[0].get('text', 'Sorry, I could not process your request.') if rasa_response else 'Sorry, I could not process your request.'
    return {
        "id": f"chatcmpl-{int(time.time())}",
        "object": "chat.completion",
        "created": int(time.time()),
        "model": model,
        "choices": [{"index": 0, "message": {"role": "assistant", "content": content}, "finish_reason": "stop"}]
    }

async def send_to_rasa(message: Dict) -> List[Dict]:
    async with aiohttp.ClientSession(timeout=aiohttp.ClientTimeout(total=10)) as session:
        async with session.post(f"{RASA_SERVER_URL}/webhooks/rest/webhook", json=message) as response:
            if response.status != 200:
                raise HTTPException(status_code=502, detail="Rasa server error")
            return await response.json()

async def generate_streaming_response(content: str, model: str):
    words = content.split(" ")
    completion_id = f"chatcmpl-{int(time.time())}"
    
    for word in words:
        chunk = {
            "id": completion_id,
            "object": "chat.completion.chunk",
            "created": int(time.time()),
            "model": model,
            "choices": [{"delta": {"content": f"{word} "}, "index": 0, "finish_reason": None}]
        }
        yield f"data: {json.dumps(chunk)}\n\n"
        await asyncio.sleep(0.1)
    
    final_chunk = {
        "id": completion_id,
        "object": "chat.completion.chunk", 
        "created": int(time.time()),
        "model": model,
        "choices": [{"delta": {}, "index": 0, "finish_reason": "stop"}]
    }
    yield f"data: {json.dumps(final_chunk)}\n\n"
    yield "data: [DONE]\n\n"

@app.post("/chat/completions")
async def chat_completions(request: ChatCompletionRequest):
    try:
        rasa_message = convert_to_rasa_message(request.messages)
        rasa_response = await send_to_rasa(rasa_message)
        
        if not request.stream:
            return convert_to_openai_response(rasa_response, request.model)
        
        content = rasa_response[0].get('text', 'Sorry, I could not process your request.') if rasa_response else 'Sorry, I could not process your request.'
        return StreamingResponse(generate_streaming_response(content, request.model), media_type="text/event-stream")
        
    except Exception:
        error_response = {
            "id": f"chatcmpl-error-{int(time.time())}",
            "object": "chat.completion",
            "created": int(time.time()),
            "model": request.model,
            "choices": [{"index": 0, "message": {"role": "assistant", "content": "Service temporarily unavailable."}, "finish_reason": "stop"}]
        }
        if request.stream:
            async def error_stream():
                yield f"data: {json.dumps(error_response)}\n\n"
                yield "data: [DONE]\n\n"
            return StreamingResponse(error_stream(), media_type="text/event-stream")
        else:
            raise HTTPException(status_code=500, detail=error_response)

@app.get("/health")
async def health_check():
    return {"status": "healthy", "timestamp": datetime.now().isoformat()}

if __name__ == "__main__":
    uvicorn.run("openai_wrapper:app", host="0.0.0.0", port=WRAPPER_PORT, reload=False)