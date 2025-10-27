## Instructions that you can give the bot are

### **Instructions for rasa bot**
These commands automatically determine the best scene for the situation:
- **Good morning** - Activates bright lighting to start your day
- **Good night** / **Going to bed** - Sets night mode for comfortable sleep
- **I'm home** / **I'm back** - Welcomes you with appropriate lighting
- **I'm leaving** / **Going out** - Turns off everything to save energy
- **Movie time** / **Let's watch a movie** - Sets ambient lighting for entertainment
- **Work mode** / **Time to work** - Activates bright lighting for productivity
- **I want to relax** / **Help me relax** - Sets relaxing mood lighting
- **Turn everything off** - Powers down all lights and scenes
- **"Set [scene] in [room]"** - Example: "Set relax mode in bedroom"
- **"Execute [scene] scene"** - Example: "Execute Relax scene"
- **"Activate [scene] in [room]"** - Example: "Activate bright scene in Work Station"
- **"Run [scene] scene"** - Example: "Run Relax scene in Conference Room"
- **"I am inside [room]"** - Example: "I am inside Conference Room" (to set context)

### **Information Commands**
Get help and discover capabilities:
- **"What can you do?"** / **"Help"** - Shows all available commands
- **"Show me all scenes"** / **"List scenes"** - Displays available lighting scenes
- **"What rooms can I control?"** / **"List rooms"** - Shows controllable rooms
- **"What scenes are in [room]?"** - Shows scenes available in specific room

### **Basic Conversation**
- **Hello** / **Hi** / **Hey** - Greet the bot
- **Thank you** / **Thanks** - Express gratitude
- **Goodbye** / **Bye** - End the conversation


## Instructions for how to set up the voice-agent
1. **Run the setup script**: Downloads all the necessary python versions and subsequent dependencies in requirements.txt.
2. **Configure Rasa**: Move into rasa_home_assistant directory
    - Train the model, if no model is present in models subdirectory, using `rasa train`
    - Start the Rasa server using `rasa run --enable-api --cors "*" --port 5005`
    - Start the action server using `rasa run actions` in a separate terminal.
    - Start the middleware server using `python openai_wrapper.py` in another terminal.
3. **Configure the livekit voice agent**: Move into voice_agent directory
    - Start the agent using `python agent.py dev` script
4. Open the livekit playground in `https://agents-playground.livekit.io/`