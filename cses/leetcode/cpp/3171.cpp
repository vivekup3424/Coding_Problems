#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    set<int> subarrayBitwiseORs(vector<int> &arr)
    {
        // since there are 4*1e8 elements, hence maximum bit required is 30
        // so our solution can be optimised for that
        set<int> allResults, prevResults;
        for (int num : arr)
        {
            set<int> currentResults;
            for (auto r : prevResults)
            {
                int value = r | num;
                currentResults.insert(value);
            }
            currentResults.insert(num);
            prevResults = currentResults;
            for (auto r : prevResults)
            {
                allResults.insert(r);
            }
        }
        return allResults;
    }

    int minimumDifference(vector<int> &nums, int k)
    {
        set<int> results = subarrayBitwiseORs(nums);
        int minDiff = INT_MAX;
        for (auto i : results)
        {
            int diff = abs(i - k);
            if (diff < minDiff)
            {
                minDiff = diff;
            }
        }
    }
};