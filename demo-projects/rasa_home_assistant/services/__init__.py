"""
Services module for Smart Home Assistant

This module provides data access and business logic services for rooms and scenes.
"""

from .room_service import (
    load_rooms_data,
    find_room_id,
    get_room_name,
    get_all_rooms,
    room_exists
)

from .scene_service import (
    load_scenes_data,
    find_scene_by_name_and_room,
    find_scenes_by_name,
    get_scenes_by_room,
    get_all_scenes,
    get_unique_scene_names
)

__all__ = [
    # Room services
    'load_rooms_data',
    'find_room_id',
    'get_room_name',
    'get_all_rooms',
    'room_exists',

    # Scene services
    'load_scenes_data',
    'find_scene_by_name_and_room',
    'find_scenes_by_name',
    'get_scenes_by_room',
    'get_all_scenes',
    'get_unique_scene_names'
]
