from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from services import (
    find_room_id,
    get_room_name,
    get_scenes_by_room,
    get_unique_scene_names
)


class ActionListScenes(Action):
    def name(self) -> Text:
        return "action_list_scenes"

    async def run(self, dispatcher, tracker, domain):
        room = next(tracker.get_latest_entity_values(
            "room"), None) or tracker.get_slot("room")

        if room:
            room_id = find_room_id(room)
            if room_id:
                room_name = get_room_name(room_id)
                room_scenes = get_scenes_by_room(room_id)
                if room_scenes:
                    # Group scenes by name (remove duplicates)
                    unique_scenes = {}
                    for scene in room_scenes:
                        scene_name = scene.sceneName
                        if scene_name not in unique_scenes:
                            unique_scenes[scene_name] = scene

                    scene_names = list(unique_scenes.keys())
                    scene_list = "• " + "\n• ".join(scene_names)

                    message = f"🎭 **Available scenes in {room_name}:**\n{scene_list}"
                    message += f"\n\n💡 You can say things like:\n• 'Turn on {scene_names[0].lower()} in {room_name}'"
                    if len(scene_names) > 1:
                        message += f"\n• 'Set {scene_names[1].lower()} mode in {room_name}'"
                    message += f"\n• 'Activate {scene_names[0].lower()}' (if you're already talking about {room_name})"
                else:
                    message = f"I don't have any scenes configured for {room_name}. Would you like to see all available scenes?"
            else:
                message = f"I couldn't find a room called '{room}'. Try asking 'what rooms can I control?' to see available rooms."
        else:
            # TODO: Consider asking for clarification instead of showing all scenes
            # when user intent is unclear (e.g., "scenes?" vs "what scenes are available?")
            names = get_unique_scene_names()
            message = f"🎭 Here are all available scenes:\n• " + \
                "\n• ".join(names)
            message += "\n\nYou can say things like:\n• 'Turn on bright lights in living room'\n• 'Set relax mode'\n• 'Activate night scene'"

        dispatcher.utter_message(text=message)
        return []
