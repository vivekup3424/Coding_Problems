#!/usr/bin/env python3
"""
Wake Word Detection using openWakeWord
Listens continuously for wake words like "alexa", "hey jarvis", etc.
"""

import os
import numpy as np
import pyaudio
from openwakeword.model import Model
from typing import Callable, Optional
import threading
import time


class WakeWordDetector:
    """
    Continuous wake word detection using openWakeWord.
    Supports multiple wake word models and customizable detection callbacks.
    """
    
    # Audio configuration optimized for wake word detection
    CHUNK_SIZE = 1280  # 80ms at 16kHz (recommended by openWakeWord)
    SAMPLE_RATE = 16000  # 16kHz required by openWakeWord
    CHANNELS = 1  # Mono audio
    FORMAT = pyaudio.paInt16
    
    def __init__(
        self,
        wake_word_models: list[str] = None,
        inference_framework: str = "onnx",
        detection_threshold: float = 0.5,
        vad_threshold: float = 0.5
    ):
        """
        Initialize wake word detector.
        
        Args:
            wake_word_models: List of wake word model names to load
                             (e.g., ["alexa", "hey_jarvis", "hey_mycroft"])
                             If None, loads all available models
            inference_framework: Framework for inference ("onnx" or "tflite")
            detection_threshold: Confidence threshold for wake word detection (0.0-1.0)
            vad_threshold: Voice activity detection threshold (0.0-1.0)
        """
        self.detection_threshold = detection_threshold
        self.vad_threshold = vad_threshold
        self.is_running = False
        self.detection_callback: Optional[Callable[[str, float], None]] = None
        
        # Initialize openWakeWord model
        print("🔧 Loading openWakeWord models...")
        self.model = Model(
            wakeword_models=wake_word_models,
            inference_framework=inference_framework
        )
        
        # Get loaded model information
        self.loaded_models = list(self.model.models.keys())
        print(f"✅ Loaded wake word models: {', '.join(self.loaded_models)}")
        
        # Initialize PyAudio
        self.audio = pyaudio.PyAudio()
        self.stream: Optional[pyaudio.Stream] = None
        
    def set_detection_callback(self, callback: Callable[[str, float], None]):
        """
        Set callback function to be called when wake word is detected.
        
        Args:
            callback: Function that takes (wake_word: str, confidence: float)
        """
        self.detection_callback = callback
        
    def _audio_callback(self, in_data, frame_count, time_info, status):
        """PyAudio stream callback for processing audio chunks."""
        if status:
            print(f"⚠️  Audio stream status: {status}")
            
        # Convert audio bytes to numpy array
        audio_data = np.frombuffer(in_data, dtype=np.int16)
        
        # Run wake word detection
        prediction = self.model.predict(audio_data)
        
        # Check each model for detections
        for wake_word, confidence in prediction.items():
            if confidence >= self.detection_threshold:
                print(f"🎯 Wake word detected: '{wake_word}' (confidence: {confidence:.2f})")
                if self.detection_callback:
                    # Run callback in separate thread to avoid blocking audio
                    threading.Thread(
                        target=self.detection_callback,
                        args=(wake_word, confidence),
                        daemon=True
                    ).start()
                    
        return (in_data, pyaudio.paContinue)
        
    def start(self, device_index: Optional[int] = None):
        """
        Start listening for wake words.
        
        Args:
            device_index: PyAudio device index for microphone (None for default)
        """
        if self.is_running:
            print("⚠️  Wake word detector is already running")
            return
            
        print(f"🎤 Starting wake word detection...")
        print(f"   Listening for: {', '.join(self.loaded_models)}")
        print(f"   Detection threshold: {self.detection_threshold}")
        
        try:
            # Open audio stream
            self.stream = self.audio.open(
                format=self.FORMAT,
                channels=self.CHANNELS,
                rate=self.SAMPLE_RATE,
                input=True,
                input_device_index=device_index,
                frames_per_buffer=self.CHUNK_SIZE,
                stream_callback=self._audio_callback
            )
            
            self.is_running = True
            self.stream.start_stream()
            print("✅ Wake word detection started. Say your wake word!")
            
        except Exception as e:
            print(f"❌ Failed to start wake word detection: {e}")
            self.stop()
            raise
            
    def start_blocking(self, device_index: Optional[int] = None):
        """
        Start listening for wake words in blocking mode.
        Will run until stop() is called or KeyboardInterrupt.
        
        Args:
            device_index: PyAudio device index for microphone (None for default)
        """
        self.start(device_index)
        
        try:
            while self.is_running:
                time.sleep(0.1)
        except KeyboardInterrupt:
            print("\n🛑 Stopping wake word detection...")
            self.stop()
            
    def stop(self):
        """Stop wake word detection and cleanup resources."""
        if not self.is_running:
            return
            
        print("🛑 Stopping wake word detection...")
        self.is_running = False
        
        if self.stream:
            self.stream.stop_stream()
            self.stream.close()
            self.stream = None
            
        print("✅ Wake word detection stopped")
        
    def cleanup(self):
        """Cleanup all resources."""
        self.stop()
        if self.audio:
            self.audio.terminate()
            
    def list_audio_devices(self):
        """List all available audio input devices."""
        print("\n🎤 Available Audio Devices:")
        print("-" * 60)
        
        for i in range(self.audio.get_device_count()):
            device_info = self.audio.get_device_info_by_index(i)
            if device_info['maxInputChannels'] > 0:  # Only show input devices
                print(f"Device {i}: {device_info['name']}")
                print(f"  Sample Rate: {int(device_info['defaultSampleRate'])} Hz")
                print(f"  Channels: {device_info['maxInputChannels']}")
                print()


def main():
    """Example usage of WakeWordDetector."""
    
    def on_wake_word_detected(wake_word: str, confidence: float):
        """Callback when wake word is detected."""
        print(f"\n🔔 WAKE WORD TRIGGERED: '{wake_word}' (confidence: {confidence:.2f})")
        print("   (In production, this would trigger your voice agent)")
        print()
    
    # Create detector with specific models
    # Available models: "alexa", "hey_jarvis", "hey_mycroft", "timer", etc.
    detector = WakeWordDetector(
        wake_word_models=["alexa"],  # Use "alexa" as wake word
        detection_threshold=0.5,  # Adjust sensitivity (lower = more sensitive)
    )
    
    # Optionally list available audio devices
    # detector.list_audio_devices()
    
    # Set callback
    detector.set_detection_callback(on_wake_word_detected)
    
    try:
        # Start detection (blocking mode)
        detector.start_blocking()
    finally:
        detector.cleanup()


if __name__ == "__main__":
    main()
