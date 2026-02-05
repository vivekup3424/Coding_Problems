class Solution:
    def recurse_tribonacci(self, n: int) -> int:
        match n:
            case 0:
                return 0
            case 1:
                return 1
            case 2:
                return 1
            case _:
                return self.recurse_tribonacci(n-1) + self.recurse_tribonacci(n-2) + self.recurse_tribonacci(n-3)
    
    def tribonacci(self, n: int) -> int:
        if n == 0:
            return 0
        if n <= 2:
            return 1
        
        first, second, third = 0, 1, 1
        for _ in range(3, n + 1):
            first, second, third = second, third, first + second + third
        return third