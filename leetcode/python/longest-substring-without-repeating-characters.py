from collections import defaultdict
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_length = 0
        left = 0
        char_freq: defaultdict[str,int] = defaultdict(int)
        for right in range(len(s)):
            char_freq[s[right]]+=1
            while char_freq[s[right]]>1:
                char_freq[s[left]]-=1
                left+=1
            max_length = max(max_length, (right-left+1))
        return max_length