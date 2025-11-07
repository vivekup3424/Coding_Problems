from typing import Text, Dict, Any
import nats
import json
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet
from services import (
    extract_and_match_room,
    extract_and_match_scene
)
from config.constants import NATS_TOKEN, NATS_HOST, NATS_PORT, SITE_ID


class ActionExecuteScene(Action):
    def name(self) -> Text:
        return "action_execute_scene"

    def _get_intent_to_scene_mapping(self) -> Dict[str, Dict[str, str]]:
        """Map contextual intents to specific scenes"""
        return {
            "good_night": {
                "scene_name": "Night",
                "message": "Good night! I've set the cozy Night scene so the lights dim and you're ready to wind down."
            },
            "good_morning": {
                "scene_name": "Bright",
                "message": "Good morning! Bright scene is on—energizing light to kickstart your day."
            },
            "want_relax": {
                "scene_name": "Relax",
                "message": "Relax mode set. Soft ambient lighting is on—take a deep breath and unwind."
            },
            "leaving_home": {
                "scene_name": "All off",
                "message": "All off—I've powered everything down safely as you head out."
            },
            "coming_home": {
                "scene_name": "Bright",
                "message": "Welcome home! Bright scene is on to greet you—let me know if you want a different mood."
            },
            "going_to_bed": {
                "scene_name": "Night",
                "message": "Night mode set. Lights are dimmed for a restful sleep. Sweet dreams!"
            },
            "movie_time": {
                "scene_name": "Relax",
                "message": "Movie mode set. Ambient lights lowered—enjoy your show!"
            },
            "work_mode": {
                "scene_name": "Bright",
                "message": "Work mode activated. Bright balanced lighting to help you focus and stay productive."
            },
            "ac_on": {
                "scene_name": "AC on",
                "message": "AC is on. Cooling started—let me know if you'd like to tweak the comfort."
            },
            "ac_off": {
                "scene_name": "AC off",
                "message": "AC is off. Saving energy—turn it back on anytime."
            },
            "party_scene": {
                "scene_name": "Party",
                "message": "Party mode! Colorful scene engaged—have fun and let me know when to change the vibe."
            },
            "reading_mode": {
                "scene_name": "Reading",
                "message": "Reading lights set. Focused warm lighting for comfy page turning. Enjoy!"
            },
            "coffee_time": {
                "scene_name": "Coffee",
                "message": "Coffee time! Bright, alert lighting—perfect for a fresh cup and a boost."
            },
            "rain_mood": {
                "scene_name": "Rain",
                "message": "Rain mood set. Gentle cool ambience—great for focus or a reflective break."
            },
            "romantic_mood": {
                "scene_name": "Romantic",
                "message": "Romantic mood set. Soft warm hues for an intimate, relaxed atmosphere."
            },
            "cool_mode": {
                "scene_name": "Cool",
                "message": "Cool mode set. Fresh clean lighting profile is active—let me know if you want to switch moods."
            }
        }

    async def _execute_via_nats(self, scene_id: int, room_id: str, scene_name: str, room_name: str) -> bool:
        """Execute scene via NATS messaging"""
        try:
            nc = await nats.connect(f"nats://{NATS_TOKEN}@{NATS_HOST}:{NATS_PORT}")
            payload = {
                "action": "EXECUTE_SCENE",
                "data": {
                    "sceneId": int(scene_id),
                    "sceneRoom": room_id
                }
            }
            
            print(f"Executing scene: {scene_name} (ID: {scene_id}) in {room_name} (ID: {room_id})")
            print(f"NATS payload: {json.dumps(payload, indent=2)}")
            
            await nc.publish(f"{SITE_ID}-KIOTP-RPC", json.dumps(payload).encode())
            await nc.close()
            return True
            
        except Exception as e:
            print(f"ERROR executing scene: {str(e)}")
            return False

    async def run(self, dispatcher: CollectingDispatcher, tracker: Tracker, domain: Dict[Text, Any]):
        intent = tracker.latest_message['intent']['name']
        print(f"Intent: {intent}")
        
        # Step 1: Extract and match room context
        room_mention = next(tracker.get_latest_entity_values("room"), None)
        if room_mention:
            print(f"Room mentioned: {room_mention}")
            room_name, room_id, slot_events = extract_and_match_room(tracker)
        else:
            # Use existing room context from slots
            room_id = tracker.get_slot("room_id")
            room_name = tracker.get_slot("room")
            slot_events = []
        
        # Step 2: Determine scene - either from intent mapping or entity
        scene_name = None
        custom_message = None
        
        intent_mapping = self._get_intent_to_scene_mapping()
        if intent in intent_mapping:
            # Contextual intent (e.g., "good night" -> "Night" scene)
            scene_info = intent_mapping[intent]
            scene_name = scene_info["scene_name"]
            custom_message = scene_info["message"]
            print(f"Using intent mapping: {intent} -> {scene_name}")
        else:
            # Explicit scene command (e.g., "execute relax in workstation")
            scene_name = next(tracker.get_latest_entity_values("scene"), None) or tracker.get_slot("scene")
        
        # Step 3: Validate we have required data
        if not scene_name:
            dispatcher.utter_message(response="utter_ask_which_scene")
            return slot_events
        
        if not room_id:
            dispatcher.utter_message(
                text="I need to know which room you're referring to. Try saying something like 'Turn on bright lights in the living room'."
            )
            return slot_events
        
        # Step 4: Find the scene using fuzzy matching
        scene_data = extract_and_match_scene(scene_name, room_id)
        
        if not scene_data:
            dispatcher.utter_message(
                text=f"I couldn't find the scene '{scene_name}' in {room_name}. Would you like to see available scenes?"
            )
            return slot_events
        
        # Step 5: Execute the scene via NATS
        success = await self._execute_via_nats(
            scene_data.sceneId, 
            room_id, 
            scene_data.sceneName, 
            room_name
        )
        
        if success:
            if custom_message:
                # Use custom message for contextual intents
                dispatcher.utter_message(text=custom_message)
            else:
                # Use generic message for explicit commands
                dispatcher.utter_message(text=f"'{scene_data.sceneName}' set in {room_name}.")
        else:
            dispatcher.utter_message(
                text="Connection issue. Please try again."
            )
        
        return slot_events 

