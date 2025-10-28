from dotenv import load_dotenv

from livekit import agents
from livekit.agents import AgentSession, Agent, ConversationItemAddedEvent, RoomInputOptions
from livekit.plugins import (
    openai,
    cartesia,
    deepgram,
    noise_cancellation,
    silero,
)
import os
import signal
import asyncio
from datetime import datetime, timedelta

load_dotenv()

# Define Rasa goodbye utterances
GOODBYE_PHRASES = [
    "Goodbye! Have a wonderful day!",
    "See you later! Let me know if you need anything!",
    "Bye! Your home is in good hands!",
]

# Inactivity timeout in seconds (e.g., 30 seconds)
INACTIVITY_TIMEOUT = 30

class Assistant(Agent):
    def __init__(self) -> None:
        super().__init__(instructions="You are a helpful voice AI assistant.")

async def entrypoint(ctx: agents.JobContext):
    # Track last activity time
    last_activity = datetime.now()
    inactivity_task = None
    
    async def check_inactivity():
        """Monitor for inactivity and shutdown if timeout exceeded"""
        nonlocal last_activity
        while True:
            await asyncio.sleep(5)  # Check every 5 seconds
            time_since_activity = (datetime.now() - last_activity).total_seconds()
            
            if time_since_activity >= INACTIVITY_TIMEOUT:
                print(f"\nNo activity for {INACTIVITY_TIMEOUT} seconds. Shutting down...")
                os.kill(os.getpid(), signal.SIGINT)
                break
    
    session = AgentSession(
        stt=deepgram.STT(model="nova-3", language="en-US"),
        llm=openai.LLM.with_ollama(model="llama3.1-8b", base_url="http://localhost:8881/"), 
        tts=cartesia.TTS(model="sonic-2", voice="f786b574-daa5-4673-aa0c-cbe3e8534c02"),
        # vad=silero.VAD.load(),
    )
    
    @session.on("conversation_item_added")
    def on_conversation_item_added(event: ConversationItemAddedEvent):
        nonlocal last_activity
        last_activity = datetime.now()
        
        print(f"New conversation item added: {event.item.content}")
        for content_item in event.item.content:
            for phrase in GOODBYE_PHRASES:
                if phrase.strip().lower() in content_item.strip().lower():
                    print(f"Goodbye phrase detected: '{phrase}'. Shutting down the session.")
                    os.kill(os.getpid(), signal.SIGINT)
        
    
    await session.start(
        room=ctx.room,
        agent=Assistant(),
        room_input_options=RoomInputOptions(
            noise_cancellation=noise_cancellation.BVC(),
        ),
    )
    
    await ctx.connect()
    
    inactivity_task = asyncio.create_task(check_inactivity())
    
    await session.generate_reply(
        instructions="Greet the user and offer your assistance."
    )

if __name__ == "__main__":
    agents.cli.run_app(agents.WorkerOptions(entrypoint_fnc=entrypoint))