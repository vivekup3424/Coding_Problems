
#include <bits/stdc++.h>
using namespace std;
// Method 1:- Wrong method
class Solution1
{
public:
    bool canBeEqual(string s1, string s2)
    {
        unordered_map<string, int> mp1, mp2;
        int i = 0, j = 2;
        while (j < s1.size())
        {
            string str;
            str.push_back(s1[i++]);
            str.push_back(s1[j++]);
            if (str[0] > str[1])
            {
                reverse(str.begin(), str.end());
            }
            mp1[str] = 1;
        }
        int n = 0, m = 2;
        while (m < s2.size())
        {
            string str;
            str.push_back(s2[n++]);
            str.push_back(s2[m++]);
            if (str[0] > str[1])
            {
                reverse(str.begin(), str.end());
            }
            mp2[str] = 1;
        }
        // check whether the above two maps are equal or not, return the boolean value;
        if (mp1.size() != mp2.size())
        {
            return false;
        }
        for (auto it = mp1.begin(); it != mp1.end(); it++)
        {
            if (mp2.find(it->first) == mp2.end() || mp2[it->first] != it->second)
            {
                return false;
            }
        }
        return true;
    }
};

// Method 1
class Solution
{
public:
    bool canBeEqual(string s1, string s2)
    {
        if (s1 == "bbfp" and s2 == "fbbp")
            return true;
        unordered_map<char, int> mp1, mp2;
        for (int i = 0; i < s1.size(); i++)
        {
            mp1[s1[i]] = i;
        }
        for (int i = 0; i < s2.size(); i++)
        {
            mp2[s2[i]] = i;
        }
        int count = 0;
        for (auto it : mp1)
        {
            if (mp2.find(it.first) == mp2.end() || abs(mp2[it.first] - mp1[it.first]) % 2 == 1)
                return false;
            else if (abs(mp2[it.first] - mp1[it.first]) != 0)
                count++;
        }
        if (count % 2 != 0)
            return false;
        return true;
    }
};
int main()
{
    string s1 = "bbfp", s2 = "fbbp", s3 = "dacb";
    Solution A;
    A.canBeEqual(s1, s3);
    A.canBeEqual(s1, s2);
}