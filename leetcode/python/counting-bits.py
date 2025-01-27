from typing import List

class Solution:
    def countBits(self, n: int) -> List[int]:
        dp = [0 for _ in range(n + 1)]
        for i in range(1, n + 1):
            if i % 2 == 0:
                dp[i] = dp[i // 2]
            else:
                dp[i] = dp[i // 2] + 1
        return dp[n]
    def convertToBinary(self, n: int) -> str:
        return bin(n)[2:]

def main():
    n = 10
    A = Solution()
    for i in range(n + 1):
        print(A.countBits(i), A.convertToBinary(i))

if __name__ == "__main__":
    main()
