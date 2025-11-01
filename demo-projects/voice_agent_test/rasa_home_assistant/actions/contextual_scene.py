from typing import Text, Optional, Dict, Any
import nats
import json
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet
from services import (
    load_rooms_data,
    find_room_id,
    get_room_name
)
from config.constants import NATS_HOST, NATS_PORT, NATS_TOKEN, SITE_ID


class ActionContextualScene(Action):
    # Constants for better maintainability
    ALL_OFF_SCENE_ID = "150"
    DEFAULT_ROOM = "Work Station 2"

    def name(self) -> Text:
        return "action_contextual_scene"

    async def _execute_scene_via_nats(self, scene_id: str, room_id: str) -> bool:
        """
        Execute a scene via NATS messaging.

        Args:
            scene_id: The scene ID to execute
            room_id: The room ID where to execute the scene

        Returns:
            bool: True if successful, False otherwise
        """
        nc = None
        try:
            nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
            payload = {
                "action": "EXECUTE_SCENE",
                "data": {
                    "sceneId": int(scene_id),
                    "sceneRoom": room_id
                }
            }
            await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
            return True
        except Exception as e:
            print(
                f"ERROR: Failed to execute scene {scene_id} in room {room_id}: {e}")
            return False
        finally:
            if nc:
                await nc.close()

    async def handle_all_rooms(self, dispatcher: CollectingDispatcher, intent: str) -> list:
        """Handle actions that affect all rooms"""
        rooms = load_rooms_data()

        if intent in ["leaving_home", "turn_off_everything"]:
            success_count = 0
            failed_rooms = []

            for room in rooms:
                if await self._execute_scene_via_nats(self.ALL_OFF_SCENE_ID, room._id):
                    success_count += 1
                else:
                    failed_rooms.append(room.roomName)

            # Provide detailed feedback
            if success_count > 0:
                if intent == "leaving_home":
                    message = f"Safe travels! I've turned off lights in {success_count} rooms for you. Have a great time!"
                else:
                    message = f"All done! Everything is now off in {success_count} rooms. Is there anything else you need?"

                if failed_rooms:
                    message += f"\nNote: Had trouble with {len(failed_rooms)} room(s): {', '.join(failed_rooms[:3])}"
                    if len(failed_rooms) > 3:
                        message += f" and {len(failed_rooms) - 3} more"

                dispatcher.utter_message(text=message)
            else:
                dispatcher.utter_message(
                    text="Sorry, I'm having trouble turning off the lights right now. Please check your connection and try again.")

        return []

    def _get_scene_mapping(self) -> Dict[str, Dict[str, str]]:
        """Get the mapping of intents to scene configurations"""
        return {
            "good_night": {
                "scene_id": "154",
                "scene_name": "Night",
                "message": "Good night! Sweet dreams! Your night lighting is now set."
            },
            "good_morning": {
                "scene_id": "151",
                "scene_name": "Bright",
                "message": "Good morning! Have a wonderful day!I've brightened everything up for you."
            },
            "want_relax": {
                "scene_id": "152",
                "scene_name": "Relax",
                "message": "Time to unwind! I've set a relaxing mood. Anything else you need?"
            },
            "leaving_home": {
                "scene_id": "150",
                "scene_name": "All off",
                "message": "Safe travels! I've turned everything off for you"
            },
            "coming_home": {
                "scene_id": "151",
                "scene_name": "Bright",
                "message": "Welcome home! I've brightened things up to welcome you back!"
            },
            "going_to_bed": {
                "scene_id": "154",
                "scene_name": "Night",
                "message": "Sleep well! Night mode is active. Rest easy!"
            },
            "movie_time": {
                "scene_id": "152",
                "scene_name": "Relax",
                "message": "Enjoy your movie! Perfect ambient lighting is set. Get the popcorn ready!"
            },
            "work_mode": {
                "scene_id": "151",
                "scene_name": "Bright",
                "message": "Let's get productive! Bright lighting activated for focused work."
            },
            "turn_off_everything": {
                "scene_id": "150",
                "scene_name": "All off",
                "message": "Everything is now turned off. Anything else you need?"
            }
        }

    def _get_default_room_mapping(self) -> Dict[str, str]:
        """Get the mapping of intents to default rooms"""
        return {
            "good_night": "Testing Room",  # Bedroom-like
            "good_morning": self.DEFAULT_ROOM,  # Start day in main area
            "going_to_bed": "Testing Room",  # Bedroom-like
            "want_relax": self.DEFAULT_ROOM,  # Default to main workspace
            "movie_time": "Testing Room",  # Entertainment room
            "work_mode": self.DEFAULT_ROOM,  # Office
            "leaving_home": "all",  # All rooms
            "coming_home": self.DEFAULT_ROOM,  # Main area
            "turn_off_everything": "all"  # All rooms
        }

    async def run(self, dispatcher: CollectingDispatcher, tracker: Tracker, domain: Dict[Text, Any]) -> list:
        intent = tracker.latest_message['intent']['name']
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")

        # Enhanced room handling
        room_id = None
        room_name = None

        if room:
            # User specified a room - convert to ID and name
            room_id = find_room_id(room)
            if not room_id:
                dispatcher.utter_message(
                    text=f"I couldn't find a room called '{room}'. Try asking 'what rooms can I control?'"
                )
                return []
            room_name = get_room_name(room_id)
        else:
            # No room specified - check if we have room context from recent conversation
            recent_room = tracker.get_slot("requested_room")

            if recent_room:
                room_id = find_room_id(recent_room)
                if not room_id:
                    dispatcher.utter_message(
                        text=f"I lost track of the room '{recent_room}'. Could you tell me which room you're in?"
                    )
                    return []
                room_name = get_room_name(room_id)
                print(f"DEBUG: Using recent room context: {room_name}")
            else:
                # No room specified and no recent context - use sensible defaults
                default_rooms = self._get_default_room_mapping()
                default_room = default_rooms.get(intent, self.DEFAULT_ROOM)

                if default_room == "all":
                    # Handle multi-room scenarios
                    return await self.handle_all_rooms(dispatcher, intent)
                else:
                    room_id = find_room_id(default_room)
                    if not room_id:
                        dispatcher.utter_message(
                            text="I couldn't pick a default room. Which room should I use?"
                        )
                        return []
                    room_name = default_room

        scene_mapping = self._get_scene_mapping()

        if intent in scene_mapping:
            scene_info = scene_mapping[intent]

            if room_id and await self._execute_scene_via_nats(scene_info["scene_id"], room_id):
                # Send contextual message with room info
                if room_name and room_name != self.DEFAULT_ROOM:
                    message = scene_info["message"] + f" (in {room_name})"
                else:
                    message = scene_info["message"]

                dispatcher.utter_message(text=message)
                # Set room context for future commands
                return [SlotSet("requested_room", room_name)]
            else:
                dispatcher.utter_message(
                    text="Sorry, I couldn't set the scene for you right now. Please check your connection and try again.")
                return []

        # Fallback for unrecognized intents
        dispatcher.utter_message(
            text="I'm not sure how to help with that. Try asking me to control scenes or tell me how you're feeling!")
        return []
