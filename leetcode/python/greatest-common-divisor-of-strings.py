class Solution:
    @staticmethod
    def gcd(a,b):
        if(b == 0):
            return a
        else:
            return Solution.gcd(b,a%b)

    def gcdOfStrings(self, str1: str, str2: str) -> str:
        if (str1 + str2 != str2 + str1):
            return ""
        gcd = Solution.gcd(len(str1),len(str2))
        return str1[:gcd]
