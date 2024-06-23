#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minIncrementForUnique(vector<int> &nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int seen = -1;
        int counter = 0;
        for (int i = 0; i < n; i++)
        {
            if (seen < nums[i])
            {
                seen = nums[i];
            }
            else if (seen >= nums[i])
            {
                seen++;
                counter += seen - nums[i];
            }
        }
        cout << "Counter = " << counter << endl;
        return counter;
    }
};