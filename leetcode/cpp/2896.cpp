
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int isEqual(string s1, string s2)
    {
        int count = 0;
        for (int i = 0; i < s1.size(); i++)
        {
            if (s1[i] != s2[i])
            {
                count++;
            }
        }
        return count;
    }
    int minOperations(string s1, string s2, int x)
    {
        int diff = isEqual(s1, s2);
        if (diff & 1) // odd difference
        {
            return -1;
        }
        else if (diff == 0)
            return 0;
        else
        {
            vector<int> diff_indices;
            for (int i = 0; i < s1.size(); i++)
            {
                if (s1[i] != s2[i])
                {
                    diff_indices.push_back(i);
                }
            }
            vector<int> dp(diff + 1, INT_MAX);
            dp[0] = 0;
            for (int i = 1; i <= diff; i++)
            {
                dp[i] = dp[i - 1] + x;
                if (i >= 2)
                {
                    dp[i] = min(dp[i], dp[i - 2] + 2 * (diff_indices[i - 1] - diff_indices[i - 2]));
                }
            }
            return dp[diff] / 2;
        }
    }
};
int main()
{
}