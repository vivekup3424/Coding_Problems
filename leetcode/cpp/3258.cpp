#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countKConstraintSubstrings(string s, int k)
    {
        int n = s.size();
        int a = 0;
        for (int i = 0; i < n; i++)
        {
            int count0 = 0, count1 = 0;
            for (int j = 0; j < n; j++)
            {
                if (s[j] == '0')
                {
                    count0++;
                }
                else
                {
                    count1++;
                }
                if (count0 <= k || count1 <= k)
                {
                    a++;
                }
                else
                {
                    break;
                }
            }
        }
        return a;
    }
};