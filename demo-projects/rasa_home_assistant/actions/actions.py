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
        if not matches:
            return None
        if room:
            for s in matches:
                if room.lower() in s["sceneRoom"].lower():
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

                if len(matching_scenes) > 1:
                    rooms = list(set([s["sceneRoom"]
                                 for s in matching_scenes]))
                    dispatcher.utter_message(
                        text=f"I found '{scene_name}' in multiple rooms: {', '.join(rooms)}. Which room did you mean?"
                    )
                    return [SlotSet("scene_name", scene_name)]
                elif len(matching_scenes) == 1:
                    # Use the only available room
                    room = matching_scenes[0]["sceneRoom"]
                else:
                    dispatcher.utter_message(response="utter_scene_not_found")
                    return []
            else:
                dispatcher.utter_message(response="utter_ask_which_room")
                return []

        scene_data = None
        if scene_name:
            scene_data = self.find_scene(scene_name, room)
            if scene_data:
                scene_id = str(scene_data["sceneId"])
                room = room or scene_data["sceneRoom"]
            else:
                dispatcher.utter_message(
                    text=f"I couldn't find the scene '{scene_name}' in {room}. Would you like to see available scenes?"
                )
                return [SlotSet("scene_name", None)]

        if not scene_id:
            dispatcher.utter_message(response="utter_ask_which_scene")
            return []

        try:
            print(
                f"DEBUG: Executing scene - sceneId: {scene_id}, sceneRoom: {room}")

            # Publish to NATS
            nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
            payload = {"action": "EXECUTE_SCENE", "data": {
                "sceneId": int(scene_id), "sceneRoom": room}}
            if scene_data:
                payload["data"].update(
                    {"sceneName": scene_data["sceneName"], "sceneType": scene_data["sceneType"]})

            print(f"DEBUG: NATS payload: {json.dumps(payload, indent=2)}")
            await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
            await nc.close()

            name = scene_data["sceneName"] if scene_data else scene_id
            dispatcher.utter_message(response="utter_scene_executed")
            dispatcher.utter_message(
                text=f"✅ '{name}' is now active in {room}! Anything else I can help with?"
            )
            return [SlotSet("scene_id", None), SlotSet("room", None), SlotSet("scene_name", None)]

        except Exception as e:
            print(f"DEBUG: Error executing scene: {str(e)}")
            dispatcher.utter_message(response="utter_scene_error")
            dispatcher.utter_message(
                text="I'm having trouble connecting to your smart home system. Please try again in a moment."
            )
            return [SlotSet("scene_id", None), SlotSet("room", None), SlotSet("scene_name", None)]


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
            # No room specified - use intelligent defaults based on intent
            default_rooms = {
                "good_night": "Testing Room",  # Bedroom-like
                "good_morning": "Testing Room",  # Bedroom-like
                "going_to_bed": "Testing Room",  # Bedroom-like
                "want_relax": "Testing Room",  # Living room-like
                "movie_time": "Testing Room",  # Living room-like
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

                return []

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
