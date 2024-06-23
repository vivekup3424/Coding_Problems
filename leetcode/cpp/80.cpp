#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int i = 0, j = 0, length = 0;
        for (int element : nums)
        {
            if (i == 0 or i == 1 or nums[i - 2] != element)
            {
                nums[i] = element;
                i++;
            }
        }
        return i;
    }
};