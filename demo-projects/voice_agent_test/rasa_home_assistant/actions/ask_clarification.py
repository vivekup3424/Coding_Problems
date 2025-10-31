from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher


#WARN: This code is not getting used anywhere
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
                text="I can help with your lighting! Are you looking to:\n• Turn lights on/off in a specific room?\n• Set a particular scene like 'bright', 'relax', or 'night'?\n• Control all lights at once?"
            )
        elif any(word in latest_message for word in ['room', 'kitchen', 'bedroom', 'living']):
            dispatcher.utter_message(
                text="I can control different rooms! Which room would you like to control and what would you like me to do there?"
            )
        elif any(word in latest_message for word in ['scene', 'mode', 'setting']):
            dispatcher.utter_message(
                text="I can set various scenes!Try saying something like:\n• 'Set relax mode'\n• 'Turn on bright lights'\n• 'Good night' (for night lighting)\n• Or ask me to 'show all scenes'"
            )
        else:
            dispatcher.utter_message(response="utter_default")

        return []
