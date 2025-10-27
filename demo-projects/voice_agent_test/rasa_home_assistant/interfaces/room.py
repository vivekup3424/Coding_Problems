from dataclasses import dataclass
from typing import Dict, Any


@dataclass
class Room:
    _id: str
    roomName: str

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Room':
        """Create Room from dictionary (from JSON)"""
        return cls(
            _id=data['_id'],
            roomName=data['roomName']
        )
