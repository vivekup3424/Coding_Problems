
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> Freq;
        for (auto num : nums)
        {
            Freq[num]++;
        }
    }
};
int main()
{
}