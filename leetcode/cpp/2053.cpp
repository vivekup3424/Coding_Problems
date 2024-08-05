#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string kthDistinct(vector<string> &arr, int k)
    {
        unordered_map<string, int> mp;
        for (string s : arr)
        {
            mp[s]++;
        }
        int counter = k;
        for (string s : arr)
        {
            if (mp[s] == 1)
            {
                counter--;
                if (counter == 0)
                {
                    return s;
                }
            }
        }
        return "";
    }
};