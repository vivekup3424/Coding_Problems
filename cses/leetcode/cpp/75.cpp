// use three pointers, and then follow algo just like quicksort
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int n = nums.size();
        int i = 0, j = 0, k = n - 1;
        while (j < k)
        {
            if (nums[j] == 0)
            {
                swap(nums[i], nums[j]);
                        }
            else if (nums[j] == 2)
            {
                swap(nums[j], nums[k]);
                k--;
            }
            j++;
        }
        return;
    }
};
int main()
{
}