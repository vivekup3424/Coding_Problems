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
from datetime import datetime, timedelta
import asyncio

load_dotenv()

# Define Rasa goodbye utterances
GOODBYE_PHRASES = [
    "Goodbye! Have a wonderful day!",
    "See you later! Let me know if you need anything!",
    "Bye! Your home is in good hands!",
]
INACTIVITY_TIMEOUT = 30 #30 seconds

class Assistant(Agent):
    def __init__(self) -> None:
        super().__init__(instructions="You are a helpful voice AI assistant.")

async def entrypoint(ctx: agents.JobContext):
    last_activity = datetime.now()
    inactivity_task = None

    async def monitor_inactivity():
        nonlocal last_activity
        while True:
            await asyncio.sleep(1)
            print("Checking for inactivity...")
            elapsed = (datetime.now() - last_activity).total_seconds()
            if elapsed > INACTIVITY_TIMEOUT:
                print("Inactivity timeout reached. Shutting down the session.")
                os.kill(os.getpid(), signal.SIGINT)
    session = AgentSession(
        stt=deepgram.STT(model="nova-3", language="multi"),
        llm=openai.LLM.with_ollama(model="llama3.1-8b", base_url="http://localhost:8881/"), 
        tts=cartesia.TTS(model="sonic-2", voice="f786b574-daa5-4673-aa0c-cbe3e8534c02"),
        vad=silero.VAD.load(),
    )

    @session.on("conversation_item_added")
    def on_conversation_item_added(event: ConversationItemAddedEvent):
        nonlocal last_activity
        last_activity = datetime.now()
        print("last_activity updated:", last_activity)
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
    inactivity_task = asyncio.create_task(monitor_inactivity()) 
    await ctx.connect()
    await session.generate_reply(
        instructions="Greet the user and offer your assistance."
    )

if __name__ == "__main__":
    agents.cli.run_app(agents.WorkerOptions(entrypoint_fnc=entrypoint))