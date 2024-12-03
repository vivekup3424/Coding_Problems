from typing import List


class Solution:
    def addSpaces(self, s: str, spaces: List[int]) -> str:
        output = ""
        spaceSet = {spaces[i] for i in range(len(spaces))}
        for i in range(len(s)):
            if i in spaceSet:
                output += " "
            output += s[i]
        return output
