from collections import defaultdict
from typing import DefaultDict, List
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        res = defaultdict(list) #mapping character count to list of anagrams
        for s in strs:
            count =  [0] * 26
            for c in s:
                count[ord(c) - ord('a')] += 1
            res[tuple(count)].append(s)
        print(res.values())
        return res.values()
