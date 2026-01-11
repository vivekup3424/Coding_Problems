class Solution:
    def residuePrefixes(self,s: str)->int:
        st:set[str]= set()
        count = 0
        for i in range(len(s)):
            st.add(s[i])
            if (i+1)%3 == len(st):
                count+=1
        return count