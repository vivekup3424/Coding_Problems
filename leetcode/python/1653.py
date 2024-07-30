class Solution:
    def minimumDeletions(self, s: str) -> int:
        pivot = -1
        for i in range(len(s)):
            if s[i] == 'b':
                pivot = i
                break
        count = 0
        for i in range(0,pivot):
            if s[i] == 'b':
                count += 1
        for i in range(len(s)-1,pivot,-1):
            if s[i] == 'a':
                count += 1
        return count