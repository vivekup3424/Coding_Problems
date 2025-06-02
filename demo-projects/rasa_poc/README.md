# RASA Home Automation Chatbot

This project implements a conversational AI assistant using RASA for controlling smart home devices including fans, air conditioning, and lighting systems.

## Features

- **Fan Control**: Turn on/off fans, adjust fan speeds
- **Air Conditioning**: Control AC units, adjust temperature, change modes
- **Lighting**: Control lights, adjust brightness, change colors and modes
- **Natural Language Understanding**: Supports natural language commands
- **Multi-room Support**: Control devices in specific rooms or areas

## Project Structure

```
├── config.yml          # RASA NLU and Core configuration
├── domain.yml          # Domain definition (intents, entities, slots, responses, actions)
├── endpoints.yml       # External service endpoints
├── data/
│   ├── nlu.yml         # NLU training data
│   ├── stories.yml     # Conversation stories
│   └── rules.yml       # Conversation rules
├── actions/
│   ├── __init__.py
│   └── actions.py      # Custom action implementations
├── Dockerfile          # Docker configuration
└── requirements.txt    # Python dependencies
```

## Setup and Usage

### Using Docker (Recommended)

1. **Build the Docker image:**
   ```bash
   docker build -t rasa-home-automation .
   ```

2. **Train the model:**
   ```bash
   docker run -it --rm -v $(pwd):/app rasa-home-automation rasa train
   ```

3. **Start the action server:**
   ```bash
   docker run -it --rm -p 5055:5055 -v $(pwd):/app rasa-home-automation rasa run actions
   ```

4. **Run the assistant (in another terminal):**
   ```bash
   docker run -it --rm -p 5005:5005 -v $(pwd):/app rasa-home-automation rasa shell
   ```

### Local Installation

1. **Install dependencies:**
   ```bash
   pip install -r requirements.txt
   python -m spacy download en_core_web_md
   ```

2. **Train the model:**
   ```bash
   rasa train
   ```

3. **Start the action server:**
   ```bash
   rasa run actions
   ```

4. **Run the assistant:**
   ```bash
   rasa shell
   ```

## Example Commands

### Fan Control
- "Turn on the bedroom fan"
- "Set the living room fan to high speed"
- "Turn off all fans"

### Air Conditioning
- "Turn on the AC in the master bedroom"
- "Set temperature to 22 degrees"
- "Change AC mode to cooling"

### Lighting
- "Turn on the kitchen lights"
- "Set bedroom lights to 50% brightness"
- "Change living room lights to blue"
- "Switch to reading mode in the study"

## Customization

### Adding New Devices
1. Update `domain.yml` to add new entities and slots
2. Add training examples in `data/nlu.yml`
3. Create new stories in `data/stories.yml`
4. Implement custom actions in `actions/actions.py`

### Integration with Smart Home Systems
The custom actions in `actions/actions.py` currently simulate device control. To integrate with real smart home systems:

1. Install the appropriate libraries (e.g., `paho-mqtt`, `requests`)
2. Modify the action methods to make actual API calls or send MQTT messages
3. Add configuration for your smart home platform

## Configuration

- **NLU Pipeline**: Uses spaCy with DIET classifier for intent classification and entity extraction
- **Dialogue Management**: Combines rule-based and machine learning approaches
- **Fallback Handling**: Includes fallback mechanisms for unrecognized inputs

## Training Data

The training data includes:
- **Intents**: 15+ intents covering device control and conversation
- **Entities**: Device locations, names, speeds, temperatures, colors, modes
- **Stories**: Multi-turn conversation examples
- **Rules**: Simple intent-to-action mappings

## Next Steps

1. Test the assistant with various commands
2. Add more training data based on real usage
3. Integrate with actual smart home devices
4. Add voice interface capabilities
5. Implement user authentication and personalization
