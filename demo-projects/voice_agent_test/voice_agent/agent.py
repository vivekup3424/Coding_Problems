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

load_dotenv()

class Assistant(Agent):
    def __init__(self) -> None:
        super().__init__(instructions="You are a helpful voice AI assistant.")

async def entrypoint(ctx: agents.JobContext):
    # Configuration without turn detection (avoids ML framework dependencies)
    session = AgentSession(
        stt=deepgram.STT(model="nova-3", language="multi"),
        llm=openai.LLM.with_ollama(model="llama3.1-8b", base_url="http://localhost:8881/"), 
        tts=cartesia.TTS(model="sonic-2", voice="f786b574-daa5-4673-aa0c-cbe3e8534c02"),
        vad=silero.VAD.load(),
    )
    @session.on("conversation_item_added")
    def on_conversation_item_added(event: ConversationItemAddedEvent):
        print(f"New conversation item added: {event.item}")
        
        if hasattr(event.item, 'content') and isinstance(event.item.content, list):
            for content_part in event.item.content:
                if hasattr(content_part, 'text') and content_part.text:
                    print(f"Transcript: {content_part.text}")
                    if "goodbye" in content_part.text.lower():
                        print("Goodbye detected, ending session.")
                        session.end()
    
    await session.start(
        room=ctx.room,
        agent=Assistant(),
        room_input_options=RoomInputOptions(
            noise_cancellation=noise_cancellation.BVC(),
        ),
    )
    
    await ctx.connect()
    await session.generate_reply(
        instructions="Greet the user and offer your assistance."
    )

if __name__ == "__main__":
    agents.cli.run_app(agents.WorkerOptions(entrypoint_fnc=entrypoint))
