from collections import deque

class Solution:
    def isValid(self,s):
        stk = deque()
        for c in s:
            if c=='(':
                stk.append('(')
            elif len(stk)==0 and c==')':
                return False
            else:
                stk.pop()
        return len(stk)==0
        
    def naiveMethod(self,s:str)->int:
        maxCount = 0
        for i in range(len(s)):
            for j in range(i,len(s)):
                temp = s[i:j+1]
                if self.isValid(temp):
                    if len(temp)>maxCount:
                        maxCount = len(temp)
    
    def dynamicApproach(self,s:str)->int:
        """
        dp[i] = length of largest valid substring ending at index i
        dp[i] for '(' = 0, as no valid substring ends with '('
        """
        n = len(s)
        dp = [0 for _ in range(n)]
    def longestValidParentheses(self, s: str) -> int:
        stk = deque()
        count, maxCount = 0, 0
        for c in s:
            if c == '(':
                stk.append('(')
            elif len(stk) == 0 and c == ')':
                count = 0
            else:
                stk.pop()
                count += 1
            if count > maxCount:
                maxCount = count
        return maxCount

def main():
    solution = Solution()
    solution.naiveMethod("(()")
    # test_cases = [
    #     "(()",                  
    #     ")()())",              
    #     "",                     
    #     "(((((",                
    #     ")))))",                
    #     "()(()))",              
    #     "(()(((()",             
    #     "()()()",              
    #     "(()())",               
    #     "())(())((()))",        
    # ]

    # for i, test_case in enumerate(test_cases, 1):
    #     result = solution.longestValidParentheses(test_case)
    #     print(f"Test Case {i}: Input: '{test_case}' -> Output: {result}")

if __name__ == "__main__":
    main()
