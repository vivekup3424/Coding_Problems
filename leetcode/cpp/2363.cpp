
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>> &items1, vector<vector<int>> &items2)
    {
        map<int, int> mp; // value to weight
        for (vector<int> p : items1)
        {
            if (mp[p[0]] == 0)
            {
                mp[p[0]] = p[1];
            }
            else
            {
                mp[p[0]] += p[1];
            }
        }
        for (vector<int> p : items2)
        {
            if (mp[p[0]] == 0)
            {
                mp[p[0]] = p[1];
            }
            else
            {
                mp[p[0]] += p[1];
            }
        }
        vector<vector<int>> ans;
        for (auto it : mp)
        {
            vector<int> v;
            v.push_back(it.first);
            v.push_back(it.second);
            ans.push_back(v);
        }
        return ans;
    }
};
int main()
{
}