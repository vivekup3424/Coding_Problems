import collections
class Solution:
    def getHash(self,s : str):
        count  = [0] * 26
        for c in s:
            count[c-'a'] +=1
        seed=0
        for i in range(26):
            seed = seed*31 +count[i]
        return seed
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        grouped_Anagrams = collections.defaultdict((list))
        for s in strs:
            hash = self.getHash(s)
            grouped_Anagrams[hash].append(s)
        return list(grouped_Anagrams.values())

