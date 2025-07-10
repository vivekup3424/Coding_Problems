"""
Room service for managing room data and operations
"""
from typing import List, Optional
import json
from interfaces import Room
from config.constants import ROOMS_DATA_PATH


def load_rooms_data() -> List[Room]:
    """Load rooms data from rooms.json file"""
    try:
        with open(ROOMS_DATA_PATH, 'r') as f:
            data = json.load(f)
            return [Room.from_dict(room) for room in data]
    except Exception as e:
        print(f"Error loading rooms data: {e}")
        return []


def find_room_id(room_name: str) -> Optional[str]:
    """Convert room name to room ID"""
    if not room_name:
        return None

    rooms = load_rooms_data()
    room_name_lower = room_name.lower().strip()

    for room in rooms:
        if room.roomName.lower() == room_name_lower:
            return room._id

    return None


def get_room_name(room_id: str) -> Optional[str]:
    """Convert room ID to friendly room name"""
    if not room_id:
        return None

    rooms = load_rooms_data()
    for room in rooms:
        if room._id == room_id:
            return room.roomName

    return None


def get_all_rooms() -> List[Room]:
    """Get all available rooms"""
    return load_rooms_data()


def room_exists(room_name: str) -> bool:
    """Check if a room exists by name"""
    return find_room_id(room_name) is not None
