#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minheap;
        for (int i = 0; i < nums.size(); i++)
        {
            minheap.push({nums[i], i});
        }
        for (int i = 0; i < k; i++)
        {
            auto p = minheap.top();
            minheap.pop();
            p.first *= multiplier;
            minheap.push(p);
        }
        while (minheap.size() > 0)
        {
            auto p = minheap.top();
            minheap.pop();
            nums[p.second] = p.first;
        }
        return nums;
    }
};