from collections import defaultdict
class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        mp = defaultdict(int)
        for item, weight in items1:
            mp[item]+=weight
        for item, weight in items2:
            mp[item]+=weight
        ans = []
        for item,weight in mp.items():
            ans.append([item,weight])
        ans = sorted(ans)
        return ans