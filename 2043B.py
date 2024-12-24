#odd digits are 1,3,5,7,9
from collections import defaultdict
dp = defaultdict()
def factorial(n):
    global dp
    for i in range(0,n+1):
        if (i == 0 or i == 1):
            dp[i] = 1
        else:
            dp[i] = i * dp[i-1]
    return dp[n]
        
# def solve(n,d):
#     if ((factorial(n)*d) % 3 == 0):
#         print(3)
#     if (d == 5 or d == 0):
#         print(5)
#     if ((factorial(n)*d)%9 == 0):
#         print(9)

print(factorial(int(1e9)))