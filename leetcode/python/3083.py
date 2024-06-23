class Solution:
    def isSubstringPresent(self, s: str) -> bool:
        hashset = set()
        for l in range(1, len(s)):
            a = s[l-1]+s[l]
            hashset.add(a)
            b = s[l]+s[l-1]
            if b in hashset:
                return True
        return False