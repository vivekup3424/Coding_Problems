from typing import List
class Solution:
    def minimumBoxes(self, apples: List[int], capacity: List[int])-> int:
        total_apples = sum(apples)
        capacity.sort(key=lambda x: -x)
        boxes_used = 0
        while total_apples > 0 and boxes_used < len(capacity):
            total_apples -= capacity[boxes_used]
            boxes_used += 1
        return boxes_used if total_apples <= 0 else -1