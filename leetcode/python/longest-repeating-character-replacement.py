from collections import defaultdict
class Solution:
    def characterReplacement(self, s: str, k : int)-> int:
        freq_map: defaultdict[str,int] = defaultdict(int)
        max_freq, max_char = 0, None
        for r in range(len(s)):
            freq_map[s[r]]+=1
            if(freq_map[s[r]] > max_freq):
                max_freq = freq_map[s[r]]
                max_char = s[r]
        
        if max_char == None:
            return 8008