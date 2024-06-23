#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        int l = 0, r = s.size() - 1;
        while (l < r)
        {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }
    string longestPalindrome1(string s)
    {
        // generate ll substrings
        vector<string> substrings;
        for (int i = 0; i < s.size(); i++)
        {
            string temp;
            for (int j = i; j < s.size(); j++)
            {
                temp.push_back(s[j]);
                substrings.push_back(temp);
            }
        }
        // print all the substrings
        for (string str : substrings)
        {
            cout << str << " ";
        }
        cout << endl;
        // check for palindrome properties from all the strings
        int max_len = 0, max_str = "";
        return s;
    }
};
int main()
{
    string str = "cbbd";
    Solution A;
    A.longestPalindrome1(str);
}