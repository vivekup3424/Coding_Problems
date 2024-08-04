from typing import List
class Solution:

    def encode(self, strs: List[str]) -> str:
        ans = ""
        for s in strs:
            ans += str(len(s)) + "#" + s
        return ans
    def decode(self, s: str) -> List[str]:
        ans = []
        i = 0
        while i < len(s):
            j = i
            #getting the integer(length of the string)
            while s[j]!='#':
                j+=1
            length = int(s[i:j])
            i = j + 1 #skipping over the '#'
            ans.append(s[i:i+length])
            j = i+length
            i = j
        return ans
