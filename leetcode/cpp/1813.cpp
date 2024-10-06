#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<string> stringSplit(string s)
    {
        vector<string> v;
        int i = 0, n = s.size();
        string temp = "";
        while (i < n)
        {
            if (s[i] == ' ')
            {
                v.push_back(temp);
                temp = "";
            }
            else
            {
                temp.push_back(s[i]);
            }
        }
        return v;
    }
    int longestCommonSubsequenceLength(vector<string> s1, vector<string> s2)
    {
        int n = s1.size(), m = s2.size();
        int dp[n + 1][m];
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < m + 1; j++)
            {
                dp[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m];
    }
    bool areSentencesSimilar(string sentence1, string sentence2)
    {
        vector<string> s1, s2;
        s1 = stringSplit(sentence1);
        s2 = stringSplit(sentence2);
        int l = longestCommonSubsequenceLength(s1, s2);
        if (l == min(s1.size(), ))
    }
};
