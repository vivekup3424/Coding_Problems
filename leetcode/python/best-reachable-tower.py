from typing import List

class Solution:
    def bestTower(self, towers: List[List[int]], center: List[int], radius: int) -> List[int]:
        cx, cy = center
        best_tower = [-1, -1]
        max_quality = -1
        
        for tower in towers:
            x, y, q = tower
            manhattan_dist = abs(x - cx) + abs(y - cy)
            if manhattan_dist <= radius:
                if q > max_quality:
                    max_quality = q
                    best_tower = [x, y]
                elif q == max_quality:
                    if [x, y] < best_tower:
                        best_tower = [x, y]
        
        return best_tower
