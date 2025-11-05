from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from services import extract_and_match_room


class ActionSetRoomContext(Action):
    def name(self) -> Text:
        return "action_set_room_context"

    async def run(self, dispatcher: CollectingDispatcher, tracker: Tracker, domain):
        room_mention = next(tracker.get_latest_entity_values("room"), None)
        print(f"Extracted room entity from user message: {room_mention}")
        
        # Use the shared utility to handle fuzzy matching and slot creation
        room_name, _, slot_events = extract_and_match_room(tracker)
        
        dispatcher.utter_message(text=f"Now in {room_name}.")
        return slot_events