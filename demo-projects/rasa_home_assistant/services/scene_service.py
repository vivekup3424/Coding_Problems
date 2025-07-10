"""
Scene service for managing scene data and operations
"""
from typing import List, Optional
import json
from interfaces import Scene
from config.constants import SCENES_DATA_PATH


def load_scenes_data() -> List[Scene]:
    """Load scenes data from scenes.json file"""
    try:
        with open(SCENES_DATA_PATH, 'r') as f:
            data = json.load(f)
            return [Scene.from_dict(scene) for scene in data]
    except Exception as e:
        print(f"Error loading scenes data: {e}")
        return []


def find_scene_by_name_and_room(scene_name: str, room_id: str) -> Optional[Scene]:
    """Find a scene by name in a specific room"""
    scenes = load_scenes_data()

    for scene in scenes:
        if (scene.sceneName.lower() == scene_name.lower() and
                scene.sceneRoom == room_id):
            return scene

    return None


def find_scenes_by_name(scene_name: str) -> List[Scene]:
    """Find all scenes with the given name across all rooms"""
    scenes = load_scenes_data()
    return [s for s in scenes if s.sceneName.lower() == scene_name.lower()]


def get_scenes_by_room(room_id: str) -> List[Scene]:
    """Get all scenes available in a specific room"""
    scenes = load_scenes_data()
    return [s for s in scenes if s.sceneRoom == room_id]


def get_all_scenes() -> List[Scene]:
    """Get all available scenes"""
    return load_scenes_data()


def get_unique_scene_names() -> List[str]:
    """Get all unique scene names across all rooms"""
    scenes = load_scenes_data()
    return list(set(s.sceneName for s in scenes))
