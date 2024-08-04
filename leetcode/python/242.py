class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        temp1 = sorted(s)
        temp2 = sorted(t)
        print(temp1)
        print(temp2)
        if(len(temp1) != len(temp2)):
            return False
        for i in range(len(temp1)):
            if(temp1[i] != temp2[i]):
                return False
        return True
