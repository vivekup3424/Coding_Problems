// important code
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
        {
            return n;
        }
        int i = 1, j = 1;
        while (i < n)
        {
            if (nums[i] != nums[i - 1])
            {
                nums[j++] = nums[i++];
            }
            else
            {
                i++;
            }
        }
        return j;
    }
};
int main()
{
}