#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumPushes(string word)
    {
        unordered_map<char, int> mp;
        for (char w : word)
        {
            mp[w]++;
        }
        // printing the frequency map now
        for (auto it : mp)
        {
            cout << it.first << "=>" << it.second << endl;
        }
        int count = 0;
        int sum = 0;
        set<char> special_chars = {'1', '*', '0', '#'};
        for (auto it : mp)
        {
            if (special_chars.count())
        }
    }
};