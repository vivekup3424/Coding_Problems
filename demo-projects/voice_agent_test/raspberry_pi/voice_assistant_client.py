#!/usr/bin/env python3
"""
Raspberry Pi Voice Assistant Client
Integrates wake word detection with LiveKit room connection for Alexa-like experience.
"""

import asyncio
import os
import signal
import sys
from typing import Optional
from dotenv import load_dotenv

from livekit import rtc, api
from wake_word_detector import WakeWordDetector

# Load environment variables
load_dotenv()


class VoiceAssistantClient:
    """
    Raspberry Pi voice assistant client.
    Listens for wake word, then connects to LiveKit room for conversation.
    """
    
    def __init__(
        self,
        livekit_url: str,
        livekit_api_key: str,
        livekit_api_secret: str,
        wake_word: str = "alexa",
        room_name_prefix: str = "voice-assistant"
    ):
        """
        Initialize voice assistant client.
        
        Args:
            livekit_url: LiveKit server URL
            livekit_api_key: LiveKit API key
            livekit_api_secret: LiveKit API secret
            wake_word: Wake word to listen for
            room_name_prefix: Prefix for LiveKit room names
        """
        self.livekit_url = livekit_url
        self.livekit_api_key = livekit_api_key
        self.livekit_api_secret = livekit_api_secret
        self.wake_word = wake_word
        self.room_name_prefix = room_name_prefix
        
        # State management
        self.wake_word_detector: Optional[WakeWordDetector] = None
        self.current_room: Optional[rtc.Room] = None
        self.is_in_conversation = False
        self.loop: Optional[asyncio.AbstractEventLoop] = None
        
        # Configuration
        self.conversation_timeout = 30  # seconds of silence before ending conversation
        self.user_identity = "raspberry-pi-client"
        
    def setup_wake_word_detector(self):
        """Initialize wake word detector."""
        print(f"🔧 Setting up wake word detection for '{self.wake_word}'...")
        
        self.wake_word_detector = WakeWordDetector(
            wake_word_models=[self.wake_word],
            detection_threshold=0.5
        )
        
        # Set callback for wake word detection
        self.wake_word_detector.set_detection_callback(self._on_wake_word_detected)
        
    def _on_wake_word_detected(self, wake_word: str, confidence: float):
        """
        Callback when wake word is detected.
        Triggers connection to LiveKit room.
        """
        if self.is_in_conversation:
            print(f"⚠️  Already in conversation, ignoring wake word")
            return
            
        print(f"\n🔔 Wake word '{wake_word}' detected! (confidence: {confidence:.2f})")
        print("   Connecting to voice agent...")
        
        # Schedule room connection in the event loop
        if self.loop and self.loop.is_running():
            asyncio.run_coroutine_threadsafe(
                self._start_conversation(),
                self.loop
            )
        else:
            print("❌ Event loop not running, cannot start conversation")
            
    async def _start_conversation(self):
        """Start a conversation session by connecting to LiveKit room."""
        if self.is_in_conversation:
            return
            
        try:
            self.is_in_conversation = True
            
            # Stop wake word detection while in conversation
            if self.wake_word_detector:
                self.wake_word_detector.stop()
                
            # Generate room name
            import time
            room_name = f"{self.room_name_prefix}-{int(time.time())}"
            
            # Create access token
            token = api.AccessToken(self.livekit_api_key, self.livekit_api_secret)
            token.with_identity(self.user_identity) \
                 .with_name("Raspberry Pi") \
                 .with_grants(api.VideoGrants(
                     room_join=True,
                     room=room_name,
                     can_publish=True,
                     can_subscribe=True
                 ))
            
            # Create and configure room
            self.current_room = rtc.Room()
            
            @self.current_room.on("participant_connected")
            def on_participant_connected(participant: rtc.RemoteParticipant):
                print(f"✅ Agent connected: {participant.name}")
                
            @self.current_room.on("participant_disconnected")
            def on_participant_disconnected(participant: rtc.RemoteParticipant):
                print(f"👋 Agent disconnected: {participant.name}")
                # End conversation when agent leaves
                asyncio.create_task(self._end_conversation())
                
            @self.current_room.on("track_subscribed")
            def on_track_subscribed(
                track: rtc.Track,
                publication: rtc.TrackPublication,
                participant: rtc.RemoteParticipant
            ):
                if track.kind == rtc.TrackKind.KIND_AUDIO:
                    print("🔊 Receiving audio from agent")
                    # Audio will be automatically played through default output
                    
            @self.current_room.on("data_received")
            def on_data_received(data: rtc.DataPacket):
                print(f"📩 Data received: {data.data.decode('utf-8')}")
                
            # Connect to room
            print(f"🔗 Connecting to room: {room_name}")
            await self.current_room.connect(self.livekit_url, token.to_jwt())
            print(f"✅ Connected to LiveKit room")
            
            # Publish microphone audio
            # Note: This is a simplified version. In production, you'd want to:
            # 1. Capture audio from the same mic used for wake word
            # 2. Handle audio device configuration properly
            # 3. Add error handling for audio capture
            
            # For now, we'll wait for the agent to respond
            # The agent will join the room and start the conversation
            
            # Set up conversation timeout
            await asyncio.sleep(self.conversation_timeout)
            
            # If we're still in conversation after timeout, end it
            if self.is_in_conversation:
                print(f"⏱️  Conversation timeout ({self.conversation_timeout}s), ending session")
                await self._end_conversation()
                
        except Exception as e:
            print(f"❌ Error during conversation: {e}")
            await self._end_conversation()
            
    async def _end_conversation(self):
        """End current conversation and return to wake word listening."""
        if not self.is_in_conversation:
            return
            
        print("\n👋 Ending conversation...")
        
        try:
            # Disconnect from room
            if self.current_room:
                await self.current_room.disconnect()
                self.current_room = None
                
        except Exception as e:
            print(f"⚠️  Error disconnecting from room: {e}")
            
        finally:
            self.is_in_conversation = False
            
            # Resume wake word detection
            print("🎤 Returning to wake word listening mode...")
            if self.wake_word_detector:
                self.wake_word_detector.start()
                
    async def run(self):
        """Run the voice assistant client."""
        # Store event loop reference
        self.loop = asyncio.get_event_loop()
        
        # Setup wake word detector
        self.setup_wake_word_detector()
        
        # Setup signal handlers for graceful shutdown
        def signal_handler(sig, frame):
            print("\n🛑 Shutting down...")
            if self.wake_word_detector:
                self.wake_word_detector.stop()
            sys.exit(0)
            
        signal.signal(signal.SIGINT, signal_handler)
        signal.signal(signal.SIGTERM, signal_handler)
        
        # Start wake word detection
        print("\n" + "=" * 60)
        print("🤖 Raspberry Pi Voice Assistant Ready!")
        print("=" * 60)
        print(f"Wake word: '{self.wake_word}'")
        print(f"Say '{self.wake_word}' to start a conversation")
        print("Press Ctrl+C to exit")
        print("=" * 60 + "\n")
        
        # Start wake word detection in blocking mode
        self.wake_word_detector.start()
        
        # Keep the async loop running
        try:
            while True:
                await asyncio.sleep(1)
        except KeyboardInterrupt:
            print("\n🛑 Shutting down...")
        finally:
            if self.wake_word_detector:
                self.wake_word_detector.cleanup()
            if self.current_room:
                await self.current_room.disconnect()


async def main():
    """Main entry point."""
    # Load configuration from environment
    livekit_url = os.getenv("LIVEKIT_URL")
    livekit_api_key = os.getenv("LIVEKIT_API_KEY")
    livekit_api_secret = os.getenv("LIVEKIT_API_SECRET")
    wake_word = os.getenv("WAKE_WORD", "alexa")
    
    # Validate configuration
    if not all([livekit_url, livekit_api_key, livekit_api_secret]):
        print("❌ Error: Missing required environment variables")
        print("   Please set: LIVEKIT_URL, LIVEKIT_API_KEY, LIVEKIT_API_SECRET")
        print("   Copy .env.example to .env and fill in your values")
        sys.exit(1)
        
    # Create and run client
    client = VoiceAssistantClient(
        livekit_url=livekit_url,
        livekit_api_key=livekit_api_key,
        livekit_api_secret=livekit_api_secret,
        wake_word=wake_word
    )
    
    await client.run()


if __name__ == "__main__":
    asyncio.run(main())
