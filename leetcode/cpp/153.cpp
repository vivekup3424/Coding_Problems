#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        // find the position of min_element
        int n = nums.size();
        int l = 0, r = n - 1;
        int mid = (l + r) / 2;
        while (l < r)
        {
            mid = (l + r) / 2;
            if (nums[l] > nums[r])
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        return mid = ()
    }
};

int main()
{
    vector<int> v = {2, 1};
    Solution A;
    A.findMin(v);
}