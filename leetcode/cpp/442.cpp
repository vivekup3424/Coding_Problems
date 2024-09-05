#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            nums[nums[i] - 1] *= -1;
        }
        for (int i = 0; i < n; i++)
        {
            cout << i << " " << nums[i] << endl;
        }
        return {};
    }
};
int main()
{
    vector<int> v = {4, 3, 2, 7, 8, 2, 3, 1};
    Solution().findDuplicates(v);
}