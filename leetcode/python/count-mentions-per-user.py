from collections import defaultdict
from typing import List
class Solution:
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:
        mentionCount,onlineTime = defaultdict(int), defaultdict(int)
        for i in range(numberOfUsers):
            currentUser = f"id{id}"
            mentionCount(currentUser) = 0
            onlineTime(currentUser) = 0
        for event in events:
            if event[0] == "OFFLINE":
