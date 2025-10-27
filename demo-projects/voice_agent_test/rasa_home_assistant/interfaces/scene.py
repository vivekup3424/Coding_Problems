from dataclasses import dataclass
from typing import Dict, Any


@dataclass
class Scene:
    sceneId: int
    sceneName: str
    sceneRoom: str
    sceneType: int

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Scene':
        """Create Scene from dictionary (from JSON)"""
        return cls(
            sceneId=data['sceneId'],
            sceneName=data['sceneName'],
            sceneRoom=data['sceneRoom'],
            sceneType=data['sceneType']
        )
