#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        // get the total of xor bits
        int total = accumulate(nums.begin(), nums.end(),
                               0, bit_xor<int>());
    }
};