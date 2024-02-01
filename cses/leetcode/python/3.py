class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        l,r = 0, 0
        st = set()
        maxLen = 0
        while r < n:
            #if set already contains the given letter,
            #move the left pointer
            while s[r] in st:
                st.remove(s[l])
                l+=1
            
            st.add(s[r])
            r+=1
            maxLen = max(maxLen, r-l)
        return maxLen
