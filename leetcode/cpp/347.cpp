#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        map<int, int> freq_map;
        for (auto i : nums)
        {
            freq_map[i]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        // Storing frequency and element in minHeap of size k
        for (auto it : freq_map)
        {
            if (minHeap.size() == k)
            {
                if (it.second > minHeap.top().second)
                {
                    minHeap.pop();
                }
                else
                {
                    // Do nothing
                    continue;
                }
            }
            minHeap.push({it.second, it.first});
        }
        vector<int> ans;
        while (minHeap.empty() == false)
        {
            ans.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    vector<int> result = solution.topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements: ";
    for (int num : result)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
