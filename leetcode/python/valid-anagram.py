from collections import defaultdict
class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        char_freq: defaultdict[str, int] = defaultdict(int)
        for c in s:
            char_freq[c] += 1
        for c in t:
            char_freq[c] -= 1
        for count in char_freq.values():
            if count != 0:
                return False
        return True
