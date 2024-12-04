class Solution:
    def canMakeSubsequence(self, str1: str, str2: str) -> bool:
        i, j = 0, 0
        while i < len(str1) and j < len(str2):
            if str1[i] == str2[j] or str1[(i + i) % 26] == str2[j]:
                j += 1
            i += 1
        return j == len(str2)


str1 = "abc"
str2 = "ad"
print(Solution().canMakeSubsequence(str1, str2))

sdvnsd
ldsknvs
