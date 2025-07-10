"""
Smart Home Interface Module

This module provides type-safe interfaces for rooms and scenes
in the Rasa smart home assistant system.

Classes:
    - Room: TypedDict for room data structure
    - Scene: TypedDict for scene data structure

Usage:
    from interfaces import Room, Scene
    
    # Use for type hints in your actions
    def process_room(room: Room) -> str:
        return room["roomName"]
    
    def process_scene(scene: Scene) -> int:
        return scene["sceneId"]
"""

from .room import Room
from .scene import Scene

__all__ = [
    'Room',
    'Scene'
]

__version__ = "1.0.0"
__author__ = "Smart Home Assistant"
