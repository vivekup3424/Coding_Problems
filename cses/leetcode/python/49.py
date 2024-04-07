import collections


class Solution:
    def get_hashed_value(self, s: str) -> int:
        count = [0] * 26
        for c in s:
            count[ord(c) - ord("a")] += 1
        seed = 0
        for i in range(26):
            seed = seed * 31 + count[i]
        return seed

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        grouped_anagrams = collections.defaultdict(list)
        for s in strs:
            hashed_value = self.get_hashed_value(s)
            grouped_anagrams[hashed_value].append(s)
        return list(grouped_anagrams.values())
