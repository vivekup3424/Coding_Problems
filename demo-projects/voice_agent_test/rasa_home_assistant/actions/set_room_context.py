from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet
from services import find_room_id, get_room_name


class ActionSetRoomContext(Action):
    """Stores the room mentioned by the user as the current context."""

    def name(self) -> Text:
        return "action_set_room_context"

    async def run(self, dispatcher: CollectingDispatcher, tracker: Tracker, domain):
        #dafaults to the Home
        room_mention = next(tracker.get_latest_entity_values("room"), "Home")

        if not room_mention:
            dispatcher.utter_message(
                text="I didn't catch which room you're in. Could you repeat that?"
            )
            return []

        room_id = find_room_id(room_mention)
        if not room_id:
            dispatcher.utter_message(
                text=f"I couldn't find a room called '{room_mention}'. Try asking 'what rooms can I control?'"
            )
            return []

        room_name = get_room_name(room_id) or room_mention
        dispatcher.utter_message(
            text=f"Got it. I'll remember you're in {room_name}."
        )
        return [SlotSet("requested_room", room_name)]
