
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maximizeSum(vector<int> &nums, int k)
    {
        int m = 0;
        for (auto n : nums)
        {
            m = max(m, n);
        }
        return ((k) * (2 * m + (k - 1))) / 2;
    }
};
int main()
{
}