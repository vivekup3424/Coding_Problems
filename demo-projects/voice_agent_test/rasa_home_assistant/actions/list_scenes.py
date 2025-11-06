from typing import Text
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from services import (
    get_scenes_by_room,
    get_unique_scene_names,
    extract_and_match_room
)


class ActionListScenes(Action):
    def name(self) -> Text:
        return "action_list_scenes"

    async def run(self, dispatcher, tracker, domain):
        # Get room from entity or slot and use fuzzy matching
        room_mention = next(tracker.get_latest_entity_values("room"), None)
        
        if room_mention:
            extract_and_match_room(tracker)
            
        room = tracker.get_slot("room")
        room_id = tracker.get_slot("room_id")
        room_scenes = get_scenes_by_room(room_id)
        if room_scenes:
            # Group scenes by name (remove duplicates)
            unique_scenes = {}
            for scene in room_scenes:
                scene_name = scene.sceneName
                if scene_name not in unique_scenes:
                    unique_scenes[scene_name] = scene

            scene_names = list(unique_scenes.keys())
            # Build a TTS-friendly spoken list: "A, B, and C"
            if len(scene_names) == 1:
                spoken = scene_names[0]
            elif len(scene_names) == 2:
                spoken = f"{scene_names[0]} and {scene_names[1]}"
            else:
                spoken = ", ".join(scene_names[:-1]) + f", and {scene_names[-1]}"

            message = f"Available scenes in {room}: {spoken}."
        else:
            message = f"No scenes for {room}."

        dispatcher.utter_message(text=message)
        return []
