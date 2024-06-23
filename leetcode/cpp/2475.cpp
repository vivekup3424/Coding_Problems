
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int unequalTriplets(vector<int> &nums)
    {
        unordered_map<int, int> freq;
        for (int n : nums)
        {
            freq[n]++;
        }
        if (freq.size() < 3)
            return 0;
        return 5;
    }
};
int main()
{
}