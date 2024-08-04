from typing import List
class Solution:

    def encode(self, strs: List[str]) -> str:
        ans = ""
        for s in strs:
            ans += str(len(s)) + "#" + s
        return ans
    def decode(self, s: str) -> List[str]:
