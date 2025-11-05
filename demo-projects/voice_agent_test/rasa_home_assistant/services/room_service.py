"""
Room service for managing room data and operations
"""
from typing import List, Optional
import json
from interfaces import Room
from config.constants import ROOMS_DATA_PATH
from thefuzz import process, fuzz
from rasa_sdk.events import SlotSet
from rasa_sdk import Tracker

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


def get_all_room_names() -> List[str]:
    """Return a list of all room friendly names (trimmed)."""
    rooms = load_rooms_data()
    return [r.roomName.strip() for r in rooms]

def extract_and_match_room(tracker: Tracker):
    """
    Extract room from mention or tracker, perform fuzzy matching, and return SlotSet events.
    Returns:
        tuple: (room_name, room_id, slot_events) where slot_events is a list of SlotSet events
    """
    room_mention = next(tracker.get_latest_entity_values("room"), None)
    print(f"Extracted room entity from tracker: {room_mention}")
    
    if not room_mention:
        room_mention = "Home"
        print("No room entity found. Defaulting to 'Home'.")
    
    # Fuzzy match the room name
    all_rooms = get_all_room_names()
    best_match, score = process.extractOne(
        room_mention, all_rooms, scorer=fuzz.token_sort_ratio
    )
    print(f"Fuzzy match result: input='{room_mention}', best_match='{best_match}', score={score}")
    
    # Get room ID and finalize room name
    room_id = find_room_id(best_match)
    room_name = get_room_name(room_id) or best_match
    print(f"Room ID for '{best_match}': {room_id}, Final room name: {room_name}")
    
    # Return room details and SlotSet events
    slot_events = [SlotSet("room", room_name), SlotSet("room_id", room_id)]
    return room_name, room_id, slot_events
