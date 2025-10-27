from typing import Text
import nats
import json
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet
from interfaces import Scene
from services import (
    load_scenes_data,
    find_room_id,
    get_room_name,
    find_scene_by_name_and_room,
    find_scenes_by_name
)
from config.constants import NATS_TOKEN, NATS_HOST, NATS_PORT, SITE_ID


class ActionExecuteScene(Action):
    def name(self) -> Text:
        return "action_execute_scene"

    # before calling this action, ensure that this room_name actually exists
    def find_scene(self, scene_name: str, room_name: str) -> Scene | None:
        """Find a scene by name, optionally filtered by room. Returns exact match or None."""
        scenes = load_scenes_data()
        scene_matches = [
            s for s in scenes if s.sceneName.lower() == scene_name.lower()]

        print(
            f"DEBUG find_scene: Looking for '{scene_name}', found {len(scene_matches)} matches")

        if not scene_matches:
            return None

        if room_name:
            room_id = find_room_id(room_name)
            if not room_id:
                return None  # Invalid room name

            print(
                f"DEBUG find_scene: Looking in room '{room_name}' (ID: {room_id})")
            for scene in scene_matches:
                print(
                    f"DEBUG find_scene: Checking scene room {scene.sceneRoom} vs {room_id}")
                if scene.sceneRoom == room_id:
                    return scene
        return None

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
                matching_scenes = find_scenes_by_name(scene_name)

                print(
                    f"DEBUG: Found {len(matching_scenes)} matching scenes for '{scene_name}'")

                if len(matching_scenes) > 1:
                    # Get friendly room names
                    room_names = []
                    for s in matching_scenes:
                        room_name = get_room_name(s.sceneRoom)
                        if room_name not in room_names:
                            room_names.append(room_name)

                    dispatcher.utter_message(
                        text=f"I found '{scene_name}' in multiple rooms: {', '.join(room_names)}. Which room did you mean?"
                    )
                    return [SlotSet("scene_name", scene_name)]
                elif len(matching_scenes) == 1:
                    # Use the only available room
                    room = matching_scenes[0].sceneRoom
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
                scene_id = str(scene_data.sceneId)
                room = room or scene_data.sceneRoom
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

            name = scene_data.sceneName if scene_data else scene_id
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
