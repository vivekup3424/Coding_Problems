// Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
//
// A subsequence of a string is a new string that is formed from the original string
// by deleting some (can be none) of the characters without disturbing the relative
// positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example 1:
// Input: s = "abc", t = "ahbgdc"
// Output: true
//
// Example 2:
// Input: s = "axc", t = "ahbgdc"
// Output: false

// Solution:-
// Just a linear traversal in enough I guess to solve it.
// Maintain two pointers at each string , move one if you find the character in anothe

#include <bits/stdc++.h>
using namespace std;

// return true if s is a subsequence of t, or false otherwise
bool pattern_matching(string t, string s, int a, int b) // a = t.size(), b = t.size()
{
    while (a > 0 and b > 0)
    {
        if (t[a - 1] == s[b - 1])
        {
            b--;
        }
        a--;
    }
    if (b > 0 and a == 0)
        return false;
    return true;
}
int main()
{
    string s = "abc", t = "ahbgdc";
    bool result = pattern_matching(t, s, t.size(), s.size());
    cout << result << "\n";
    return 0;
}