from typing import List
from collections import defaultdict
class Solution:
    def countPairs(self, words: List[str])->int:
        freq_map: defaultdict[tuple[int,...],int] = defaultdict(int)
        count = 0
        for word in words:
            temp:List[int]= []
            for i in range(1,len(word)):
                value = (ord(word[i])-ord(word[0])+26)%26
                temp.append(value)
            hashed_key = tuple(temp)
            freq_map[hashed_key]+=1
        for freq in freq_map.values():
            if freq > 1:
                count += (freq*(freq-1))//2
        return count