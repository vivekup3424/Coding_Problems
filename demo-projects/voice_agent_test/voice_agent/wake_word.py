#!/usr/bin/env python3
"""
Wake Word Detection Script for Voice Agent
Listens for "Hey Mycroft" wake word and starts the agent in console mode.
"""

import sys
import os
import subprocess
import pyaudio
import openwakeword
from openwakeword.model import Model
import numpy as np
import signal
import time
import openwakeword
from deepgram import DeepgramClient
from dotenv import load_dotenv
import io
import wave

load_dotenv()

HEY_KEE_US = os.path.expanduser("~/Downloads/hey_kee_us.onnx")
HEY_KEUS = os.path.expanduser("~/Downloads/hey_keus.onnx")
HEY_K_OOS = os.path.expanduser("~/Downloads/hey_k_oos.onnx")

# WAKE_WORD = "hey_mycroft"
# Or provide full path to your .onnx or .tflite file
AUDIO_FORMAT = pyaudio.paInt16
CHANNELS = 1
SAMPLE_RATE = 16000
CHUNK_SIZE = 1280  # 80ms chunks at 16kHz
DETECTION_THRESHOLD = 0.4  # Confidence threshold for wake word detection
POST_WAKE_DURATION = 2.0  # Seconds to record after wake word detection

class WakeWordDetector:
    def __init__(self):
        self.model = None
        self.audio = None
        self.stream = None
        self.agent_process = None
        self.running = True
        self.deepgram_client = None
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
        
        # Initialize Deepgram client
        deepgram_api_key = os.getenv("DEEPGRAM_API_KEY")
        if not deepgram_api_key:
            print("⚠️  Warning: DEEPGRAM_API_KEY not found in environment")
        else:
            self.deepgram_client = DeepgramClient(api_key=deepgram_api_key)
            print("✓ Deepgram client initialized")
    
    def _signal_handler(self, signum, frame):
        """Handle shutdown signals gracefully"""
        print("\n\nShutting down wake word detector...")
        self.running = False
        self.cleanup()
        sys.exit(0)
    
    def setup(self):
        """Initialize the wake word model and audio stream"""
        print("Initializing wake word detection...")
        
        # Initialize OpenWakeWord model
        # By default, it includes pre-trained models like "hey_mycroft"
        # openwakeword.utils.download_models()
        self.model = Model(
            wakeword_models=[HEY_KEE_US, HEY_KEUS, HEY_K_OOS],
            inference_framework="onnx"
        )
        print(f"✓ Loaded wake word models: {HEY_KEE_US}, {HEY_KEUS}")
        
        self.audio = pyaudio.PyAudio()
        
        try:
            self.stream = self.audio.open(
                format=AUDIO_FORMAT,
                channels=CHANNELS,
                rate=SAMPLE_RATE,
                input=True,
                frames_per_buffer=CHUNK_SIZE
            )
            print(f"✓ Audio stream opened (rate={SAMPLE_RATE}Hz, chunk={CHUNK_SIZE})")
        except Exception as e:
            print(f"✗ Error opening audio stream: {e}")
            raise
        
        print("\n" + "="*60)
        print(f"🎤 Listening for wake word: 'Hey Keus'")
        print(f"   Detection threshold: {DETECTION_THRESHOLD}")
        print("   Say 'Hey Keus' to activate the voice agent")
        print("   Press Ctrl+C to quit")
        print("="*60 + "\n")
    
    def detect_wake_word(self):
        """Listen for wake word in audio stream"""
        try:
            # Read audio chunk
            audio_data = self.stream.read(CHUNK_SIZE, exception_on_overflow=False)
            audio_array = np.frombuffer(audio_data, dtype=np.int16)
            
            # Get prediction from model
            prediction = self.model.predict(audio_array)
            
            # Check all available models for detection
            for model_name, score in prediction.items():
                if score >= DETECTION_THRESHOLD:
                    print(f"\nWake word detected! (confidence: {score:.2f})")
                    return True
            
            return False
            
        except Exception as e:
            print(f"Error during detection: {e}")
            return False
    
    def record_post_wake_audio(self):
        """Record audio for POST_WAKE_DURATION seconds after wake word detection"""
        print(f"🎙️  Recording for {POST_WAKE_DURATION} seconds...")
        
        num_chunks = int(SAMPLE_RATE * POST_WAKE_DURATION / CHUNK_SIZE)
        audio_frames = []
        
        try:
            for i in range(num_chunks):
                audio_data = self.stream.read(CHUNK_SIZE, exception_on_overflow=False)
                audio_frames.append(audio_data)
            
            print("✓ Recording complete")
            return b''.join(audio_frames)
        
        except Exception as e:
            print(f"Error recording audio: {e}")
            return None
    
    def transcribe_audio(self, audio_data):
        """Transcribe audio using Deepgram API"""
        if not self.deepgram_client:
            print("⚠️  Deepgram client not initialized, skipping transcription")
            return None
        
        try:
            print("🔄 Transcribing audio with Deepgram...")
            
            # Create a WAV file in memory
            wav_buffer = io.BytesIO()
            with wave.open(wav_buffer, 'wb') as wav_file:
                wav_file.setnchannels(CHANNELS)
                wav_file.setsampwidth(2)  # 16-bit audio
                wav_file.setframerate(SAMPLE_RATE)
                wav_file.writeframes(audio_data)
            
            wav_buffer.seek(0)
            audio_bytes = wav_buffer.read()
            
            # Transcribe using Deepgram - SDK v5.x uses: client.listen.v1.media.transcribe_file()
            response = self.deepgram_client.listen.v1.media.transcribe_file(
                request=audio_bytes,
                model="nova-2",
                language="en-US",
                smart_format=True,
                punctuate=True,
            )
            
            # Extract transcript
            transcript = response.results.channels[0].alternatives[0].transcript.strip()
            
            if transcript:
                print(f"✓ Transcription: '{transcript}'")
                return transcript
            else:
                print("⚠️  No speech detected in audio")
                return None
                
        except Exception as e:
            print(f"Error transcribing audio: {e}")
            import traceback
            traceback.print_exc()
            return None
    
    def start_agent(self, initial_message=None):
        """Start the voice agent in console mode"""
        print("\n" + "="*60)
        if initial_message:
            print(f"Starting voice agent with command: '{initial_message}'")
        else:
            print("Starting voice agent in console mode...")
        print("="*60 + "\n")
        
        # Get the path to agent.py (same directory as this script)
        script_dir = os.path.dirname(os.path.abspath(__file__))
        agent_script = os.path.join(script_dir, "agent.py")
        
        try:
            # Build command with optional initial message
            cmd = [sys.executable, agent_script, "console"]
            if initial_message:
                cmd.extend(["--initial-message", initial_message])
            
            # Start the agent as a subprocess with inherited stdin/stdout/stderr
            # This allows the console mode to work properly
            self.agent_process = subprocess.Popen(
                cmd,
                cwd=script_dir,
                stdin=sys.stdin,
                stdout=sys.stdout,
                stderr=sys.stderr
            )
            
            print(f"Agent started with PID: {self.agent_process.pid}")
            
            # Wait for the agent to finish
            self.agent_process.wait()
            
            print("\n" + "="*60)
            print("Voice agent session ended")
            print("Resuming wake word detection...")
            print("="*60 + "\n")
            
        except Exception as e:
            print(f"Error starting agent: {e}")
        finally:
            self.agent_process = None
    
    def run(self):
        """Main loop: listen for wake word and start agent"""
        self.setup()
        
        try:
            while self.running:
                if self.detect_wake_word():
                    # Record audio after wake word detection
                    audio_data = self.record_post_wake_audio()
                    
                    # Transcribe the recorded audio
                    initial_message = None
                    if audio_data:
                        initial_message = self.transcribe_audio(audio_data)
                    
                    # Close audio stream before starting agent
                    if self.stream:
                        self.stream.stop_stream()
                        self.stream.close()
                        self.stream = None
                    
                    # Start agent with transcribed message
                    self.start_agent(initial_message)
                    
                    # Reopen audio stream after agent exits
                    if self.audio:
                        self.stream = self.audio.open(
                            format=AUDIO_FORMAT,
                            channels=CHANNELS,
                            rate=SAMPLE_RATE,
                            input=True,
                            frames_per_buffer=CHUNK_SIZE
                        )
                        time.sleep(0.5)
                        while self.stream.get_read_available() > 0:
                            self.stream.read(self.stream.get_read_available(), exception_on_overflow=False)
                        self.model.reset()
                    print("🎤 Listening for wake word again...")
                
                # Small delay to prevent CPU overuse
                time.sleep(0.01)
                
        except KeyboardInterrupt:
            print("\n\nStopping wake word detector...")
        finally:
            self.cleanup()
    
    def cleanup(self):
        """Clean up resources"""
        if self.agent_process and self.agent_process.poll() is None:
            print("Terminating agent process...")
            self.agent_process.terminate()
            self.agent_process.wait(timeout=5)
        
        if self.stream:
            self.stream.stop_stream()
            self.stream.close()
        
        if self.audio:
            self.audio.terminate()
        
        print("Cleanup complete")

def main():
    """Entry point for wake word detection"""
    detector = WakeWordDetector()
    detector.run()

if __name__ == "__main__":
    main()
