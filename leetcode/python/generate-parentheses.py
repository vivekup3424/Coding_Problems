from typing import List
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        def recurse(n: int, s: str, num_opening: int = 0, num_closing: int = 0):
            if len(s) == 2 * n:
                result.append(s)
                return
            if num_opening < n:
                recurse(n, s + '(', num_opening + 1, num_closing)
            if num_opening > num_closing:
                recurse(n, s + ')', num_opening, num_closing + 1)

        result = []
        recurse(n, '')
        return result
A = Solution()
t = int(input("Enter the number of test cases: "))
for _ in range(t):
    n = int(input("Enter the number of parenthesis pairs: "))
    print("Resultant Parentheses:")
    print(A.generateParenthesis(n))
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")