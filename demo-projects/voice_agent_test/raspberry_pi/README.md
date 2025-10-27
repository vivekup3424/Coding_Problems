# Raspberry Pi Voice Assistant

An Alexa-like voice assistant for Raspberry Pi that integrates wake word detection with your LiveKit voice agent.

## 🎯 Features

- **Wake word detection** using openWakeWord (default: "Alexa")
- **Real-time voice communication** via LiveKit
- **Automatic conversation management** with timeout
- **Systemd service** for auto-start on boot
- **Easy setup** with automated installation script

## 📋 Requirements

### Hardware
- Raspberry Pi 4 (4GB+ recommended) or Raspberry Pi 5
- USB microphone or HAT with microphone
- Speaker or audio output device
- Internet connection

### Software
- Raspberry Pi OS (Bullseye or newer)
- Python 3.9+
- Active LiveKit server (cloud or self-hosted)

## 🚀 Quick Start

### 1. Clone and Navigate
```bash
cd /home/pi
git clone <your-repo>
cd voice_agent_test/raspberry_pi
```

### 2. Run Setup Script
```bash
chmod +x setup_pi.sh
./setup_pi.sh
```

This will:
- Install system dependencies
- Create Python virtual environment
- Install Python packages
- Download wake word models
- Configure audio devices
- Create .env file

### 3. Configure Environment
Edit `.env` with your LiveKit credentials:
```bash
nano .env
```

Required settings:
```bash
LIVEKIT_URL=wss://your-livekit-server.livekit.cloud
LIVEKIT_API_KEY=your_api_key_here
LIVEKIT_API_SECRET=your_api_secret_here
WAKE_WORD=alexa
```

### 4. Test Wake Word Detection
```bash
source venv/bin/activate
python wake_word_detector.py
```

Say "Alexa" to test detection.

### 5. Run Voice Assistant
```bash
./start.sh
```

## 🔧 Advanced Configuration

### Change Wake Word
Edit `.env` and set `WAKE_WORD` to one of:
- `alexa`
- `hey_jarvis`
- `hey_mycroft`
- Custom (requires training your own model)

### Adjust Sensitivity
In `.env`:
```bash
DETECTION_THRESHOLD=0.5  # Lower = more sensitive (0.0-1.0)
```

### Select Audio Device
List available devices:
```bash
python -c "from wake_word_detector import WakeWordDetector; WakeWordDetector().list_audio_devices()"
```

Set device in `.env`:
```bash
AUDIO_DEVICE_INDEX=2
```

## 🤖 Auto-Start on Boot

### Install Systemd Service
```bash
chmod +x install_service.sh
./install_service.sh
```

### Manage Service
```bash
# Start
sudo systemctl start voice-assistant

# Stop
sudo systemctl stop voice-assistant

# Restart
sudo systemctl restart voice-assistant

# View status
sudo systemctl status voice-assistant

# View logs
sudo journalctl -u voice-assistant -f

# Disable auto-start
sudo systemctl disable voice-assistant
```

## 📁 File Structure

```
raspberry_pi/
├── wake_word_detector.py       # Wake word detection module
├── voice_assistant_client.py   # Main client application
├── requirements.txt            # Python dependencies
├── setup_pi.sh                 # Installation script
├── install_service.sh          # Systemd service installer
├── start.sh                    # Manual start script
├── voice-assistant.service     # Systemd service file
├── .env.example               # Environment template
├── .env                       # Your configuration (create from example)
└── README.md                  # This file
```

## 🔍 Troubleshooting

### No Wake Word Detection
1. Check microphone connection: `arecord -l`
2. Test recording: `arecord -d 5 test.wav && aplay test.wav`
3. Verify correct audio device in `.env`
4. Lower detection threshold

### Can't Connect to LiveKit
1. Verify `.env` credentials are correct
2. Check internet connection
3. Ensure LiveKit server is running
4. Check firewall settings

### Service Won't Start
1. Check logs: `sudo journalctl -u voice-assistant -f`
2. Verify `.env` file exists and is configured
3. Ensure virtual environment is set up correctly
4. Check file permissions

### Audio Issues
```bash
# Install ALSA utilities
sudo apt install alsa-utils

# List audio devices
arecord -l
aplay -l

# Test microphone
arecord -d 5 -f cd test.wav
aplay test.wav

# Adjust volume
alsamixer
```

## 🔊 How It Works

1. **Wake Word Detection**: Continuously listens for wake word using openWakeWord
2. **Trigger**: When wake word detected, connects to LiveKit room
3. **Conversation**: Streams audio to/from voice agent (your existing setup)
4. **Timeout**: After 30 seconds of silence, disconnects and returns to listening
5. **Repeat**: Returns to wake word detection mode

## 🎛️ Architecture

```
┌─────────────────┐
│   Raspberry Pi  │
│                 │
│  ┌───────────┐  │      ┌──────────────┐
│  │ Wake Word │──┼─────→│ LiveKit Room │
│  │ Detection │  │      └──────┬───────┘
│  └───────────┘  │             │
│                 │             │
│  ┌───────────┐  │             ▼
│  │ LiveKit   │◄─┼──────┌─────────────┐
│  │  Client   │  │      │ Voice Agent │
│  └───────────┘  │      │  (Server)   │
│                 │      └─────────────┘
│  ┌───────────┐  │             │
│  │  Mic + 🔊 │  │             │
│  └───────────┘  │             ▼
└─────────────────┘      ┌─────────────┐
                         │ Rasa Bot +  │
                         │ OpenAI API  │
                         └─────────────┘
```

## 📝 Development

### Test Individual Components

**Wake Word Detector:**
```bash
python wake_word_detector.py
```

**Voice Client (without wake word):**
```python
from voice_assistant_client import VoiceAssistantClient
import asyncio

client = VoiceAssistantClient(url, key, secret)
asyncio.run(client.run())
```

## 🔐 Security Notes

- Keep `.env` file secure (contains API credentials)
- `.env` is in `.gitignore` - never commit it
- Use environment-specific credentials
- Consider using systemd secrets for production

## 📚 Additional Resources

- [openWakeWord Documentation](https://github.com/dscripka/openWakeWord)
- [LiveKit Documentation](https://docs.livekit.io/)
- [Raspberry Pi Audio Setup](https://www.raspberrypi.com/documentation/computers/configuration.html#audio)

## 🤝 Contributing

Issues and pull requests welcome!

## 📄 License

Same as parent project.
