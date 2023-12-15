
#include <bits/stdc++.h>
using namespace std;
// Method 1: - Stupid Method
// As I am having overflow at 23! (factorial)
const int N = 101;
long long unsigned dp[N];
int factorial(int n)
{
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
            dp[i] = 1;
        else
            dp[i] = dp[i - 1] * i;
    }
    return dp[n];
}
class Solution1
{
public:
    int uniquePaths(int m, int n)
    {
        int mx = m + n - 2;
        factorial(mx);
        int ans = dp[m + n - 2] / (dp[m - 1] * dp[n - 1]);
        return ans;
    }
};

// Method 2: Think wisely to reduce computation

int main()
{
    int m = 23, n = 12;
    Solution A;
    A.uniquePaths(m, n);
}