
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minGroupsForValidAssignment(vector<int> &nums)
    {
        unordered_map<int, int> freq;
        for (int n : nums)
        {
            freq[n]++;
        }

        int minFreq = INT_MAX;
        for (auto it : freq)
        {
            minFreq = min(minFreq, it.second);
        }

        int numGroups = 0;
        for (auto it : freq)
        {
            numGroups += ceil((it.second) / (minFreq + 1));
        }
        return numGroups;
    }
};
int main()
{
}