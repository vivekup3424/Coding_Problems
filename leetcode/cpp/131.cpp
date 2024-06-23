#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isPalindrome(string s)
    {
        int l = 0, r = s.size() - 1;
        while (l <= r)
        {
            if (s[l++] != s[r--])
            {
                return false;
            }
        }
        return true;
    }
    bool arePalindrome(vector<string> strs)
    {
        for (string str : strs)
        {
            if (isPalindrome(str) == false)
            {
                return false;
            }
        }
        return true;
    }
    vector<vector<string>> partition(string s)
    {
    }
};