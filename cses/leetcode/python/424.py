from collections import defaultdict
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        count = defaultdict(int)
        l = 0
        maxCount = 0
        maxLen = 0
        for r,c in enumerate(s):
            count[c]+=1
            maxCount = max(maxCount,count[c])
            if (r - l + 1 - maxCount) <= k:
                maxLen = max(maxLen, r - l + 1)
            while (r-l+1-maxCount > k) :
                count[s[l]]-=1
                l+=1
        return maxLen