
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int distributeCookies(vector<int> &cookies, int k)
    {
        int range = 0;
        for (auto n : cookies)
        {
            range += n;
        }
        int s1 = range / 2; // range of s1 = [Total_sum/2, Total_sum] in order to minimize the difference
        int n = cookies.size();
        bool dp[n + 1][range + 1];
        while (s1 < range)
        {

            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < s1 + 1; j++)
                {
                    if (j == 0)
                        dp[i][j] = true;
                    else if (i == 0)
                        dp[i][j] = false;
                    else if (cookies[i - 1] <= s1)
                    {
                        dp[i][j] = dp[i - 1][j - cookies[i - 1]] || dp[i - 1][j];
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
            if (dp[k][s1])
                return s1;
            s1++;
        }
        return s1;
    }
};
int main()
{
    vector<int> cookies = {8, 15, 10, 20, 8};
    int k = 2;
    Solution A;
    A.distributeCookies(cookies, k);
}