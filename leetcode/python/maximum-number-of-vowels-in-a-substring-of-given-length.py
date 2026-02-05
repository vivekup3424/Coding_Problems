class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        vowels = {"a", "e", "i", "o", "u"}
        l,r,count,n = 0,0,0,len(s)
        max_count = 0
        while r < k:
            if s[r] in vowels:
                count+=1
            r+=1
        max_count = max(max_count,count)
        while r < n:
            if s[l] in vowels:
                count-=1
            if s[r] in vowels:
                count+=1
            l+=1
            r+=1
            max_count = max(max_count,count)
        return max_count