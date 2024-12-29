#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MOD = 1e9 + 7;
    int recurse(vector<vector<int>> &memo, int i, int gc)
    {
        if (gc == 1)
        {
            return memo[i][gc] = 0;
        }
        else if (i == 0)
        {
            return memo[i][gc] = 1;
        }
        if (memo[i][gc] != -1)
        {
            return memo[i][gc];
        }
        int result = 0;
        for (int j = 2; j < 10; j++)
        {
            if (gc == 0)
            {
                result = (result + recurse(memo, i - 1, j)) % MOD;
            }
            else
            {
                result = (result + recurse(memo, i - 1, __gcd(gc, j))) % MOD;
            }
        }
        return memo[i][gc] = result % MOD;
    }
    int countNumbers(int n)
    {
        vector<vector<int>> memo(n, vector<int>(10, -1));
        return recurse(memo, n, 0);
    }
};

int main()
{
    int n;
    cin >> n;
    cout << Solution().countNumbers(n) << endl;
}