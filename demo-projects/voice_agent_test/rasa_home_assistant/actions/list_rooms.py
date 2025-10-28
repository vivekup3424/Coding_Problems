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
            dispatcher.utter_message(
                text="Sorry, I couldn't load the rooms data. Please try again later.")
            return []

        # Create a friendly list of rooms
        room_list = []
        for room in rooms:
            if room._id != "Home":  # Skip the "Home" entry as it's not a real room
                room_list.append(room.roomName)

        if room_list:
            message = f"I can control these rooms:\n• " + \
                "\n• ".join(room_list)
            message += "\n\nJust tell me what you want to do! For example:\n• 'Turn on living room lights'\n• 'Set relax mode in bedroom'\n• 'Good night' (I'll set night lighting everywhere)"
        else:
            message = "I don't see any rooms configured yet. Please check your smart home setup."

        dispatcher.utter_message(text=message)
        return []
