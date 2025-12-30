from typing import List
from collections import defaultdict
class Solution:
    def pyramidTransition(self,bottom: str,allowed: List[str])->bool:
        topMap: defaultdict[str, str] = defaultdict(str)
        for pattern in allowed:
            topMap[pattern[:2]] = pattern[2]
        #go through bottom row with two consecutive block at a time
        newRow: str = ""
        for i in range(len(bottom)-1):
            temp: str = bottom[i]+bottom[i+1]
            if temp in topMap:
                newRow+=topMap[temp]
        print(topMap)
        return False