// Longest Palindromic Substring

#include <bits/stdc++.h>
using namespace std;

// recursive way
void longestCommonSubstring(string s, string t, int index_s, int index_i, string &temp, string &maxString)
{
    if (index_i == index_s)
    {
        temp.push_back(s[index_i - 1]);
        longestCommonSubstring(s, t, index_i - 1, index_s - 1, temp, maxString);
    }
    if (index_i == 0 or index_s == 0)
    {
        return;
    }
    if (temp.length() > maxString.length())
    {
        maxString = temp;
    }
    if (index_i == index_s)
    {
        temp.push_back(s[index_i - 1]);
        longestCommonSubstring(s, t, index_i - 1, index_s - 1, temp, maxString);
    }
    else if (index_i != index_s)
    {
        temp = "";
        longestCommonSubstring(s, t, index_i - 1, index_s - 1, temp, maxString);
    }
}

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size() - 1;
        string temp = "";
        string maxString = "";
        longestCommonSubstring(s, s, n - 1, n - 1, temp, maxString);
        return maxString;
    }
};