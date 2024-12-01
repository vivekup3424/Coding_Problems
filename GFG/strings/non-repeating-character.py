from typing import DefaultDict


class Solution:
    def nonRepeatingChar(self, s):
        freq = DefaultDict(int)
        for c in s:
            freq[c] += 1
        for c in s:
            if freq[c] == 1:
                return c
        return "$"
