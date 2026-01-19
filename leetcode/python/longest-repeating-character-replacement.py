from collections import defaultdict
class Solution:
    def characterReplacement(self, s: str, k : int)-> int:
        freq_map: defaultdict[str,int] = defaultdict(int)
        max_freq, l, max_length = 0, 0, 0
        for r in range(len(s)):
            freq_map[s[r]]+=1
            if(freq_map[s[r]] > max_freq):
                max_freq = freq_map[s[r]]
            while (r - l + 1) - max_freq > k:
                freq_map[s[l]] -= 1
                l += 1
            max_length = max(max_length, (r-l+1))
        return max_length