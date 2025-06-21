from typing import Any, Text, Dict, List
import asyncio
import nats
import json
import os
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet

# Static configuration
NATS_HOST = "10.1.4.238"
NATS_PORT = 9769
NATS_TOKEN = "keus-iot-platform"
SITE_ID = "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0"


def load_scenes_data():
    """Load scenes data from scenes.json file"""
    try:
        scenes_file = os.path.join(os.path.dirname(
            __file__), "..", "data", "scenes.json")
        with open(os.path.normpath(scenes_file), 'r') as f:
            return json.load(f)
    except:
        return []


def load_rooms_data():
    """Load rooms data from rooms.json file"""
    try:
        rooms_file = os.path.join(os.path.dirname(
            __file__), "..", "data", "rooms.json")
        with open(os.path.normpath(rooms_file), 'r') as f:
            return json.load(f)
    except:
        return []


def find_room_id(room_name: str):
    """Convert room name to room ID"""
    if not room_name:
        return None

    rooms = load_rooms_data()
    room_name_lower = room_name.lower().strip()

    # Try exact match first
    for room in rooms:
        if room["roomName"].lower() == room_name_lower:
            return room["_id"]

    # Try partial match
    for room in rooms:
        if room_name_lower in room["roomName"].lower():
            return room["_id"]

    # Return as-is if no match (might be room ID already)
    return room_name


def get_room_name(room_id: str):
    """Convert room ID to friendly room name"""
    if not room_id:
        return None

    rooms = load_rooms_data()
    for room in rooms:
        if room["_id"] == room_id:
            return room["roomName"]

    return room_id  # Return as-is if not found


class ActionExecuteScene(Action):
    def name(self) -> Text:
        return "action_execute_scene"

    def find_scene(self, scene_name: str, room: str = None):
        scenes = load_scenes_data()
        matches = [s for s in scenes if s["sceneName"].lower() ==
                   scene_name.lower()]
        print(
            f"DEBUG find_scene: Looking for '{scene_name}', found {len(matches)} matches")
        if not matches:
            return None
        if room:
            # Convert room name to room ID for proper matching
            room_id = find_room_id(room)
            print(
                f"DEBUG find_scene: Looking in room '{room}' (ID: {room_id})")
            for s in matches:
                print(
                    f"DEBUG find_scene: Checking scene room {s['sceneRoom']} vs {room_id}")
                if s["sceneRoom"] == room_id:
                    return s
        return matches[0]

    async def run(self, dispatcher, tracker, domain):
        # Extract data
        scene_id = next(tracker.get_latest_entity_values(
            "scene_id"), None) or tracker.get_slot("scene_id")
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")
        scene_name = next(tracker.get_latest_entity_values(
            "scene_name"), None) or tracker.get_slot("scene_name")

        # Check if we have enough information
        if not scene_id and not scene_name:
            dispatcher.utter_message(response="utter_ask_which_scene")
            return []

        if not room:
            # If no room specified, ask for clarification
            if scene_name:
                # Check if scene exists in multiple rooms
                scenes = load_scenes_data()
                matching_scenes = [
                    s for s in scenes if s["sceneName"].lower() == scene_name.lower()]

                print(
                    f"DEBUG: Found {len(matching_scenes)} matching scenes for '{scene_name}'")

                if len(matching_scenes) > 1:
                    # Get friendly room names
                    room_names = []
                    for s in matching_scenes:
                        room_name = get_room_name(s["sceneRoom"])
                        if room_name not in room_names:
                            room_names.append(room_name)

                    dispatcher.utter_message(
                        text=f"I found '{scene_name}' in multiple rooms: {', '.join(room_names)}. Which room did you mean?"
                    )
                    return [SlotSet("scene_name", scene_name)]
                elif len(matching_scenes) == 1:
                    # Use the only available room
                    room = matching_scenes[0]["sceneRoom"]
                    print(f"DEBUG: Using room {room} for single match")
                else:
                    dispatcher.utter_message(response="utter_scene_not_found")
                    return []
            else:
                dispatcher.utter_message(response="utter_ask_which_room")
                return []

        scene_data = None
        if scene_name:
            print(f"DEBUG: Looking for scene '{scene_name}' in room '{room}'")
            scene_data = self.find_scene(scene_name, room)
            if scene_data:
                scene_id = str(scene_data["sceneId"])
                room = room or scene_data["sceneRoom"]
                print(f"DEBUG: Found scene data: {scene_data}")
            else:
                room_name = get_room_name(room) if room else "unknown room"
                dispatcher.utter_message(
                    text=f"I couldn't find the scene '{scene_name}' in {room_name}. Would you like to see available scenes?"
                )
                return [SlotSet("scene_name", None)]

        if not scene_id:
            dispatcher.utter_message(response="utter_ask_which_scene")
            return []

        try:
            # Ensure we have the room ID for the NATS payload
            room_id = find_room_id(room) if room else room
            room_name = get_room_name(room_id)

            print(
                f"DEBUG: Executing scene - sceneId: {scene_id}, sceneRoom: {room} (ID: {room_id})")

            # Publish to NATS
            nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
            payload = {"action": "EXECUTE_SCENE", "data": {
                "sceneId": int(scene_id), "sceneRoom": room_id}}
            print(payload)

            print(f"DEBUG: NATS payload: {json.dumps(payload, indent=2)}")
            await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
            await nc.close()

            name = scene_data["sceneName"] if scene_data else scene_id
            dispatcher.utter_message(response="utter_scene_executed")
            dispatcher.utter_message(
                text=f"✅ '{name}' is now active in {room_name}! Anything else I can help with?"
            )
            # Set the room context for future commands instead of clearing it
            return [SlotSet("scene_id", None), SlotSet("requested_room", room_name), SlotSet("scene_name", None)]

        except Exception as e:
            print(f"DEBUG: Error executing scene: {str(e)}")
            dispatcher.utter_message(response="utter_scene_error")
            dispatcher.utter_message(
                text="I'm having trouble connecting to your smart home system. Please try again in a moment."
            )
            return [SlotSet("scene_id", None), SlotSet("scene_name", None)]


class ActionListScenes(Action):
    def name(self) -> Text:
        return "action_list_scenes"

    async def run(self, dispatcher, tracker, domain):
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")
        scenes = load_scenes_data()

        if not scenes:
            dispatcher.utter_message(
                text="Sorry, I couldn't load the scenes data. Please try again later.")
            return []

        if room:
            room_scenes = [
                s for s in scenes if s["sceneRoom"].lower() == room.lower()]
            if room_scenes:
                names = list(set([s["sceneName"] for s in room_scenes]))
                message = f"🏠 Available scenes for {room}:\n• " + \
                    "\n• ".join(names)
                message += f"\n\nJust say something like 'activate {names[0]} in {room}' to use one!"
            else:
                message = f"I don't have any scenes configured for {room}. Would you like to see all available scenes?"
        else:
            names = list(set([s["sceneName"] for s in scenes]))
            message = f"🎭 Here are all available scenes:\n• " + \
                "\n• ".join(names)
            message += "\n\nYou can say things like:\n• 'Turn on bright lights in living room'\n• 'Set relax mode'\n• 'Activate night scene'"

        dispatcher.utter_message(text=message)
        return []


class ActionContextualScene(Action):
    def name(self) -> Text:
        return "action_contextual_scene"

    async def handle_all_rooms(self, dispatcher, intent):
        """Handle actions that affect all rooms"""
        scenes = load_scenes_data()
        rooms = load_rooms_data()

        if intent in ["leaving_home", "turn_off_everything"]:
            # Turn off all rooms
            scene_id = "150"  # All off scene
            success_count = 0

            for room in rooms:
                try:
                    nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
                    payload = {
                        "action": "EXECUTE_SCENE",
                        "data": {
                            "sceneId": int(scene_id),
                            "sceneRoom": room["_id"]
                        }
                    }
                    await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
                    await nc.close()
                    success_count += 1
                except:
                    continue

            if success_count > 0:
                if intent == "leaving_home":
                    dispatcher.utter_message(
                        text=f"✅ Safe travels! I've turned off lights in {success_count} rooms for you. Have a great time! 👋")
                else:
                    dispatcher.utter_message(
                        text=f"✅ All done! Everything is now off in {success_count} rooms. Is there anything else you need?")
            else:
                dispatcher.utter_message(
                    text="Sorry, I'm having trouble turning off the lights right now. Please try again.")

        return []

    async def run(self, dispatcher, tracker, domain):
        intent = tracker.latest_message['intent']['name']
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")

        # Enhanced room handling
        room_id = None
        room_name = None

        if room:
            # User specified a room - convert to ID and name
            room_id = find_room_id(room)
            room_name = get_room_name(room_id)
        else:
            # No room specified - check if we have room context from recent conversation
            # Look for recent room mentions in the conversation
            recent_room = tracker.get_slot("requested_room")

            if recent_room:
                room_id = find_room_id(recent_room)
                room_name = get_room_name(room_id)
                print(f"DEBUG: Using recent room context: {room_name}")
            else:
                # No room specified and no recent context - use Work Station as sensible default
                # This covers cases where user says "I want to relax" without room context
                default_rooms = {
                    "good_night": "Testing Room",  # Bedroom-like
                    "good_morning": "Work Station",  # Start day in main area
                    "going_to_bed": "Testing Room",  # Bedroom-like
                    "want_relax": "Work Station",  # Default to main workspace
                    "movie_time": "Testing Room",  # Entertainment room
                    "work_mode": "Work Station",  # Office
                    "leaving_home": "all",  # All rooms
                    "coming_home": "Work Station",  # Main area
                    "turn_off_everything": "all"  # All rooms
                }

                default_room = default_rooms.get(intent, "Work Station")

                if default_room == "all":
                    # Handle multi-room scenarios
                    return await self.handle_all_rooms(dispatcher, intent)
                else:
                    room_id = find_room_id(default_room)
                    room_name = default_room

        scene_mapping = {
            "good_night": {"scene_id": "154", "scene_name": "Night", "message": "Good night! Sweet dreams! 🌙 Your night lighting is now set."},
            "good_morning": {"scene_id": "151", "scene_name": "Bright", "message": "Good morning! Have a wonderful day! ☀️ I've brightened everything up for you."},
            "want_relax": {"scene_id": "152", "scene_name": "Relax", "message": "Time to unwind! 🧘‍♀️ I've set a relaxing mood. Anything else you need?"},
            "leaving_home": {"scene_id": "150", "scene_name": "All off", "message": "Safe travels! I've turned everything off for you 👋"},
            "coming_home": {"scene_id": "151", "scene_name": "Bright", "message": "Welcome home! 🏠 I've brightened things up to welcome you back!"},
            "going_to_bed": {"scene_id": "154", "scene_name": "Night", "message": "Sleep well! 😴 Night mode is active. Rest easy!"},
            "movie_time": {"scene_id": "152", "scene_name": "Relax", "message": "Enjoy your movie! 🎬 Perfect ambient lighting is set. Get the popcorn ready!"},
            "work_mode": {"scene_id": "151", "scene_name": "Bright", "message": "Let's get productive! 💪 Bright lighting activated for focused work."},
            "turn_off_everything": {"scene_id": "150", "scene_name": "All off", "message": "Everything is now turned off ✅ Anything else you need?"}
        }

        if intent in scene_mapping:
            scene_info = scene_mapping[intent]

            try:
                # Execute the scene
                nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
                payload = {
                    "action": "EXECUTE_SCENE",
                    "data": {
                        "sceneId": int(scene_info["scene_id"]),
                        "sceneRoom": room_id
                    }
                }

                await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
                await nc.close()

                # Send contextual message with room info
                if room_name and room_name != "Work Station":  # Don't mention default room
                    message = scene_info["message"] + f" (in {room_name})"
                else:
                    message = scene_info["message"]

                dispatcher.utter_message(text=message)

                # Set room context for future commands
                return [SlotSet("requested_room", room_name)]

            except Exception as e:
                dispatcher.utter_message(
                    text="Sorry, I couldn't set the scene for you right now.")
                return []

        # Fallback for unrecognized intents
        dispatcher.utter_message(
            text="I'm not sure how to help with that. Try asking me to control scenes or tell me how you're feeling!")
        return []


class ActionListRooms(Action):
    def name(self) -> Text:
        return "action_list_rooms"

    async def run(self, dispatcher, tracker, domain):
        rooms = load_rooms_data()

        if not rooms:
            dispatcher.utter_message(
                text="Sorry, I couldn't load the rooms data. Please try again later.")
            return []

        # Create a friendly list of rooms
        room_list = []
        for room in rooms:
            if room["_id"] != "Home":  # Skip the "Home" entry as it's not a real room
                room_list.append(room["roomName"])

        if room_list:
            message = f"🏠 I can control these rooms:\n• " + \
                "\n• ".join(room_list)
            message += "\n\nJust tell me what you want to do! For example:\n• 'Turn on living room lights'\n• 'Set relax mode in bedroom'\n• 'Good night' (I'll set night lighting everywhere)"
        else:
            message = "I don't see any rooms configured yet. Please check your smart home setup."

        dispatcher.utter_message(text=message)
        return []


class ActionAskClarification(Action):
    """Custom action to ask for clarification when the user's intent is unclear"""

    def name(self) -> Text:
        return "action_ask_clarification"

    async def run(self, dispatcher, tracker, domain):
        # Analyze what information we might be missing
        latest_message = tracker.latest_message.get('text', '').lower()

        # Check for lighting-related keywords
        if any(word in latest_message for word in ['light', 'bright', 'dim', 'dark']):
            dispatcher.utter_message(
                text="I can help with your lighting! 💡 Are you looking to:\n• Turn lights on/off in a specific room?\n• Set a particular scene like 'bright', 'relax', or 'night'?\n• Control all lights at once?"
            )
        elif any(word in latest_message for word in ['room', 'kitchen', 'bedroom', 'living']):
            dispatcher.utter_message(
                text="I can control different rooms! 🏠 Which room would you like to control and what would you like me to do there?"
            )
        elif any(word in latest_message for word in ['scene', 'mode', 'setting']):
            dispatcher.utter_message(
                text="I can set various scenes! 🎭 Try saying something like:\n• 'Set relax mode'\n• 'Turn on bright lights'\n• 'Good night' (for night lighting)\n• Or ask me to 'show all scenes'"
            )
        else:
            dispatcher.utter_message(response="utter_default")

        return []


class ActionListScenesInRoom(Action):
    """List all available scenes for a specific room"""

    def name(self) -> Text:
        return "action_list_scenes_in_room"

    async def run(self, dispatcher, tracker, domain):
        # Get the room from entity or slot
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")

        if not room:
            dispatcher.utter_message(
                text="Which room would you like to see scenes for? I can show you scenes for any of your rooms."
            )
            return []

        # Find room ID
        room_id = find_room_id(room)
        room_name = get_room_name(room_id)

        if not room_id:
            dispatcher.utter_message(
                text=f"I couldn't find a room called '{room}'. Try asking 'what rooms can I control?' to see available rooms."
            )
            return []

        # Load scenes and filter by room
        scenes = load_scenes_data()
        room_scenes = [s for s in scenes if s["sceneRoom"] == room_id]

        if not room_scenes:
            dispatcher.utter_message(
                text=f"I don't see any scenes configured for {room_name}. You might want to check your smart home setup."
            )
            return []

        # Group scenes by name (remove duplicates)
        unique_scenes = {}
        for scene in room_scenes:
            scene_name = scene["sceneName"]
            if scene_name not in unique_scenes:
                unique_scenes[scene_name] = scene

        # Create response message
        scene_names = list(unique_scenes.keys())
        scene_list = "• " + "\n• ".join(scene_names)

        message = f"🎭 **Available scenes in {room_name}:**\n{scene_list}"
        message += f"\n\n💡 You can say things like:\n• 'Turn on {scene_names[0].lower()} in {room_name}'"
        if len(scene_names) > 1:
            message += f"\n• 'Set {scene_names[1].lower()} mode in {room_name}'"
        message += f"\n• 'Activate {scene_names[0].lower()}' (if you're already talking about {room_name})"

        dispatcher.utter_message(text=message)
        return []
