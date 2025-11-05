from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from services import load_rooms_data


class ActionListRooms(Action):
    def name(self) -> Text:
        return "action_list_rooms"

    async def run(self, dispatcher, tracker, domain):
        rooms = load_rooms_data()

        if not rooms:
            dispatcher.utter_message(text="Can't load rooms right now.")
            return []

        # Create a friendly list of rooms
        room_list = []
        for room in rooms:
            room_list.append(room.roomName)

        if room_list:
            message = "**Available rooms:**\n• " + "\n• ".join(room_list)
        else:
            message = "No rooms configured."

        dispatcher.utter_message(text=message)
        return []
