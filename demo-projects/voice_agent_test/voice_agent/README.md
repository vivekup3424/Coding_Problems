# Voice Agent with Wake Word Detection

A LiveKit-based voice agent that can be activated using the wake word "Hey Mycroft".

## Features

- 🎤 Wake word detection using OpenWakeWord
- 🤖 Voice agent powered by LiveKit
- 🗣️ Speech-to-text with Deepgram
- 🧠 LLM integration with Ollama (llama3.1-8b)
- 🔊 Text-to-speech with Cartesia
- 🔇 Noise cancellation and voice activity detection

## Prerequisites

### System Dependencies

1. **PortAudio** (required for audio I/O):
   ```bash
   sudo apt-get update
   sudo apt-get install portaudio19-dev
   ```

2. **Python 3.11+**

3. **Ollama** running locally on port 8881 (for LLM)

### Python Dependencies

Install all required packages:

```bash
# Make sure you're in your virtual environment
source .venv/bin/activate  # or activate your venv

# Install dependencies
pip install -r requirements.txt
```

### Environment Variables

Create a `.env` file in the project directory with your API keys:

```env
# LiveKit credentials (optional for console mode)
LIVEKIT_URL=your_livekit_url
LIVEKIT_API_KEY=your_api_key
LIVEKIT_API_SECRET=your_api_secret

# Speech services API keys
DEEPGRAM_API_KEY=your_deepgram_api_key
CARTESIA_API_KEY=your_cartesia_api_key
```

## Usage

### Option 1: Wake Word Activation (Recommended)

Start the wake word detector that will automatically launch the agent when "Hey Mycroft" is detected:

```bash
python wake_word.py
```

The script will:
1. Listen continuously for the wake word "Hey Mycroft"
2. When detected, automatically start the voice agent in console mode
3. After the agent session ends, resume listening for the wake word
4. Press `Ctrl+C` to stop

### Option 2: Direct Console Mode

Run the agent directly in console mode without wake word detection:

```bash
python agent.py console
```

In console mode:
- Press `Ctrl+B` to toggle between text/audio input
- Press `Q` to quit

### Option 3: Development Mode

Run the agent in development mode (requires LiveKit server):

```bash
python agent.py dev
```

## Wake Word Configuration

The wake word detector uses these settings (configurable in `wake_word.py`):

```python
WAKE_WORD = "hey_mycroft"           # The wake word to detect
DETECTION_THRESHOLD = 0.5           # Confidence threshold (0.0-1.0)
SAMPLE_RATE = 16000                 # Audio sample rate in Hz
CHUNK_SIZE = 1280                   # Audio chunk size (80ms at 16kHz)
```

### Available Wake Words

OpenWakeWord comes with several pre-trained models. To see available models, check:
- `hey_mycroft` (default)
- `hey_jarvis`
- `alexa`
- And others...

To change the wake word, modify the `WAKE_WORD` constant in `wake_word.py`.

## Troubleshooting

### PortAudio Library Not Found

If you get `OSError: PortAudio library not found`:

```bash
sudo apt-get install portaudio19-dev
```

### Audio Device Issues

If the microphone is not detected, the script will list available audio devices. You can specify a device by modifying the `pyaudio.open()` call in `wake_word.py`:

```python
self.stream = self.audio.open(
    format=AUDIO_FORMAT,
    channels=CHANNELS,
    rate=SAMPLE_RATE,
    input=True,
    input_device_index=YOUR_DEVICE_INDEX,  # Add this line
    frames_per_buffer=CHUNK_SIZE
)
```

### Wake Word Not Detecting

1. **Increase microphone volume** or speak closer to the microphone
2. **Lower the threshold** in `wake_word.py`:
   ```python
   DETECTION_THRESHOLD = 0.3  # Lower = more sensitive
   ```
3. **Check background noise** - too much noise can interfere with detection

### Ollama Connection Issues

Make sure Ollama is running and accessible:

```bash
# Check if Ollama is running
curl http://localhost:8881/api/tags

# If not, start Ollama with the correct model
ollama run llama3.1-8b
```

## Project Structure

```
voice_agent/
├── agent.py              # Main voice agent implementation
├── wake_word.py          # Wake word detection script
├── requirements.txt      # Python dependencies
├── .env                  # API keys and configuration (create this)
└── README.md            # This file
```

## How It Works

1. **Wake Word Detection**: `wake_word.py` continuously monitors audio input using PyAudio
2. **Model Inference**: OpenWakeWord processes audio chunks to detect "Hey Mycroft"
3. **Agent Activation**: When detected, the script launches `agent.py console`
4. **Voice Interaction**: The agent uses:
   - Deepgram for speech-to-text
   - Ollama (llama3.1-8b) for natural language understanding
   - Cartesia for text-to-speech
   - Silero VAD for voice activity detection
5. **Session End**: After the conversation ends, returns to wake word listening

## Tips

- **Speak clearly** when saying the wake word
- **Wait for confirmation** message before speaking to the agent
- **Use headphones** to prevent echo/feedback during agent responses
- **Adjust threshold** if detection is too sensitive or not sensitive enough

## License

This project uses LiveKit Agents and various plugins. Check individual package licenses for details.
