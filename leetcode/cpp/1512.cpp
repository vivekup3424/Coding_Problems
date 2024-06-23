
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int numIdenticalPairs(vector<int> &nums)
    {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++)
        {
            m[nums[i]]++;
        }
        int sum = 0;
        for (auto a : m)
        {
            int v = a.second;
            int r = (v * (v - 1)) / 2;
            sum += r;
        }
        return sum;
    }
};
int main()
{
}