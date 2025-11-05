"""
Scene service for managing scene data and operations
"""
from typing import List, Optional
import json
from interfaces import Scene
from config.constants import SCENES_DATA_PATH
from thefuzz import process, fuzz


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


def extract_and_match_scene(scene_name: str, room_id: str) -> Optional[Scene]:
    """
    Find a scene by name in a room using fuzzy matching.
    
    Args:
        scene_name: The scene name to search for
        room_id: The room ID to search in
    
    Returns:
        Scene object if found, None otherwise
    """
    if not scene_name or not room_id:
        return None
    
    
    # Get all scenes for this room
    room_scenes = get_scenes_by_room(room_id)
    if not room_scenes:
        print(f"No scenes found in room {room_id}")
        return None
    
    # Fuzzy match the scene name
    scene_names = [s.sceneName for s in room_scenes]
    best_match, score = process.extractOne(
        scene_name, scene_names, scorer=fuzz.token_sort_ratio
    )
    print(f"Scene fuzzy match: input='{scene_name}', best_match='{best_match}', score={score}")
    
    # Find and return the matching scene
    for scene in room_scenes:
        if scene.sceneName == best_match:
            return scene
    
    return None
