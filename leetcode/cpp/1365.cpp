
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        // Method 1 is always brute force, with time = O(n^2), space = O(1)
        // Method 2
        vector<int> count(101, 0);
        vector<int> prefixSum(101, 0); // Prefix Sum Array

        // building the frequency array
        for (auto n : nums)
        {
            count[n]++;
        }
        // calculate the prefix sum array
        for (int i = 1; i < 101; i++)
        {
            prefixSum[i] = prefixSum[i - 1] + count[i - 1];
        }

        // make the result vector
        vector<int> result;
        for (auto n : nums)
        {
            result.push_back(prefixSum[n]);
        }
        return result;
    }
};
int main()
{
}