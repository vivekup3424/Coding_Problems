#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isValid(map<char, int> &mp)
    {
        return (mp['a'] % 2 == 0 and mp['e'] % 2 == 0 and mp['i'] % 2 == 0 and mp['o'] % 2 == 0 and mp['u'] % 2 == 0);
    }
    int total(map<char, int> &mp)
    {
        int l = 0;
        for (auto it : mp)
        {
            l += it.second;
        }
    }
    // eleetminicoworoep
    int bruteforce(string s)
    {
        int n = s.length();
        int maxi = 0;
        for (int i = 0; i < n; i++)
        {
            map<char, int> mp;
            for (int j = i; j < n; j++)
            {
                mp[s[j]]++;
                if (isValid(mp))
                {
                    maxi = max(maxi, total(mp));
                }
            }
        }
        return maxi;
    }
    int findTheLongestSubstring(string s)
    {
        map<char, int> mp;
        int n = s.size();
        int maxi = 0, l = 0;
        int start = 0, end = 0;
        while (end < n)
        {
            mp[s[end++]]++;
            l++;
            if (isValid(mp))
            {
                maxi = max(maxi, l);
            }
            else
            {
                while (start <= end and isValid(mp) == false)
                {
                    mp[s[start++]]--;
                    l--;
                }
            }
        }
        return maxi;
    }
};