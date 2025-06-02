# Home Automation Chatbot - Requirements Document

## Project Overview
A conversational AI assistant built with Rasa for home automation control. The assistant will enable users to control various smart home devices through natural language commands.

## Core Features

### 1. Fan Control
**Intents:**
- `turn_on_fan` - Turn on fans
- `turn_off_fan` - Turn off fans
- `adjust_fan_speed` - Change fan speed levels

**Entities:**
- `device_location` - Room/area (bedroom, living room, kitchen, etc.)
- `fan_speed` - Speed levels (low, medium, high, 1-5)
- `device_name` - Specific fan identifier (ceiling fan, table fan, etc.)

**Example Commands:**
- "Turn on the bedroom fan"
- "Set the living room fan to high speed"
- "Turn off all fans"
- "Increase fan speed in the kitchen"

### 2. Air Conditioning Control
**Intents:**
- `turn_on_ac` - Turn on air conditioning
- `turn_off_ac` - Turn off air conditioning
- `adjust_temperature` - Change temperature settings
- `change_ac_mode` - Switch AC modes (cool, heat, auto, dry, fan)
- `adjust_ac_speed` - Change AC fan speed

**Entities:**
- `device_location` - Room/area
- `temperature` - Temperature values (18-30°C)
- `ac_mode` - Operating modes (cool, heat, auto, dry, fan_only)
- `ac_speed` - Fan speed (low, medium, high, auto)
- `device_name` - Specific AC unit identifier

**Example Commands:**
- "Turn on the AC in the master bedroom"
- "Set temperature to 22 degrees"
- "Change AC mode to cooling"
- "Turn off air conditioning in all rooms"
- "Set AC to auto mode with temperature 24"

### 3. Lighting Control
**Intents:**
- `turn_on_lights` - Turn on lights
- `turn_off_lights` - Turn off lights
- `adjust_brightness` - Change light intensity
- `change_light_color` - Modify light color
- `change_light_mode` - Switch lighting modes
- `dim_lights` - Reduce brightness
- `brighten_lights` - Increase brightness

**Entities:**
- `device_location` - Room/area
- `brightness_level` - Percentage (0-100%) or descriptive (dim, bright, medium)
- `light_color` - Color names (red, blue, green, warm white, cool white, etc.)
- `light_mode` - Preset modes (reading, party, romantic, sleep, work, etc.)
- `device_name` - Specific light fixture (chandelier, bedside lamp, etc.)

**Example Commands:**
- "Turn on the kitchen lights"
- "Set bedroom lights to 50% brightness"
- "Change living room lights to blue"
- "Switch to reading mode in the study"
- "Dim the lights in the dining room"
- "Turn on warm white lights in the bedroom"
