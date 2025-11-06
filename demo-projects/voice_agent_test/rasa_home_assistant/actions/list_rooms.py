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
            # Build a TTS-friendly spoken list: "A, B, and C"
            if len(room_list) == 1:
                spoken = room_list[0]
            elif len(room_list) == 2:
                spoken = f"{room_list[0]} and {room_list[1]}"
            else:
                spoken = ", ".join(room_list[:-1]) + f", and {room_list[-1]}"

            message = f"I can control these rooms: {spoken}."
        else:
            message = "No rooms configured."

        dispatcher.utter_message(text=message)
        return []
