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

WAKE_WORD = os.path.expanduser("~/Downloads/hey_kee_us.onnx")
# WAKE_WORD = "hey_mycroft"
# Or provide full path to your .onnx or .tflite file
AUDIO_FORMAT = pyaudio.paInt16
CHANNELS = 1
SAMPLE_RATE = 16000
CHUNK_SIZE = 1280  # 80ms chunks at 16kHz
DETECTION_THRESHOLD = 0.4  # Confidence threshold for wake word detection

class WakeWordDetector:
    def __init__(self):
        self.model = None
        self.audio = None
        self.stream = None
        self.agent_process = None
        self.running = True
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
    
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
            wakeword_models=[WAKE_WORD],
            inference_framework="onnx"
        )
        print(f"✓ Loaded wake word model: {WAKE_WORD}")
        
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
    
    def start_agent(self):
        """Start the voice agent in console mode"""
        print("\n" + "="*60)
        print("Starting voice agent in console mode...")
        print("="*60 + "\n")
        
        # Get the path to agent.py (same directory as this script)
        script_dir = os.path.dirname(os.path.abspath(__file__))
        agent_script = os.path.join(script_dir, "agent.py")
        
        try:
            # Start the agent as a subprocess with inherited stdin/stdout/stderr
            # This allows the console mode to work properly
            self.agent_process = subprocess.Popen(
                [sys.executable, agent_script, "console"],
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
                    if self.stream:
                        self.stream.stop_stream()
                        self.stream.close()
                        self.stream = None
                    
                    self.start_agent()
                    
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
