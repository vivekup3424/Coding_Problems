# very similar to 2-sum problem
from typing import List


class Solution:
    def checkIfExist(self, arr: List[int]) -> bool:
        indices = set()
        for i in arr:
            if i / 2 in indices or 2 * i in indices:
                return True
            else:
                indices.add(i)
        return False
