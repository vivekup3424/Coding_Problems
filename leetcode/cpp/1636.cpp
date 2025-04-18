#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> frequencySort(vector<int> &nums)
    {
        priority_queue<pair<int, int>> pq;
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            mp[nums[i]]++;
        }
        for (auto it : mp)
        {
            pq.push({it.second, it.first});
        }
        vector<int> ans;
        while (!pq.empty())
        {
            auto it = pq.top();
            for (int i = 0; i < it.first; i++)
            {
                ans.push_back(it.second);
            }
            pq.pop();
        }
        return ans;
    }
};