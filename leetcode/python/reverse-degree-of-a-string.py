class Solution:
    def reverseDegree(self, s: str) -> int:
        sum = 0
        for i in range(len(s)):
            sum += (i+1)*((ord('z')-ord(s[i])+1))
        print(sum)