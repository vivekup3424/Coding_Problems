// use DP

#include <bits/stdc++.h>
using namespace std;
// 1.Recursion
class Solution1
{
public:
    int climbStairs(int n)
    {
        if (n == 1)
            return 1;
        else if (n == 2)
            return 2;
        else
            return climbStairs(n - 1) + climbStairs(n - 2);
    }
};
// 2. Memoization
class Solution2
{
public:
    vector<int> memo;
    int climbStairs(int n)
    {
        memo.resize(n + 1, -1);
        if (n == 1)
            return memo[1] = 1;
        else if (n == 2)
            return memo[2] = 2;
        else
        {
            memo[n] = climbStairs(n - 1) + climbStairs(n - 2);
            return memo[n];
        }
    }
};

// 3.DP
class Solution
{
public:
    int climbStairs(int n)
    {
        int dp[n + 1];
        for (int i = 1; i <= n; i++)
        {
            if (i == 1)
                dp[i] = 1; // initialization
            else if (i == 2)
                dp[i] = 2;
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
int main()
{
}