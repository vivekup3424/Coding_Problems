
#include <bits/stdc++.h>
using namespace std;
// First method recursion
class Solution1
{
public:
    int fib(int n)
    {
        if (n == 0)
            return 0;
        else if (n == 1)
            return 1;
        else
            return fib(n - 1) + fib(n - 2);
    }
};
// memoized version
class Solution
{
public:
    vector<int> memo;
    int fib(int n)
    {
        // there is a logical error, before accessing the indexed of vector
        // I need to resize it
        // I can't just directly access its index, as it causes segmentation fault
        // hence I need to allocate memory to it
        memo.resize(n + 1, -1);
        if (n == 0)
            return memo[0] = 0;
        else if (n == 1)
            return memo[1] = 1;
        else
        {
            memo[n] = (fib(n - 1) + fib(n - 2));
            return memo[n];
        }
    }
};
// bottom-up approach
class Solution
{
public:
    int fib(int n)
    {
        if (n <= 1)
            return n;

        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
int main()
{
}