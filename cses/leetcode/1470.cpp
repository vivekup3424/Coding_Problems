
#include <bits/stdc++.h>
using namespace std;
// Method 1 : Using linear space
class Solution1
{
public:
    vector<int> shuffle(vector<int> &nums, int n)
    {
        vector<int> num;
        int i = 0, j = n; // two pointer approach
        while (i < n)
        {
            num.push_back(nums[i++]);
            num.push_back(nums[j++]);
        }
        return num;
    }
};
// Method 2 : Using constant space
class Solution
{
public:
    vector<int> shuffle(vector<int> &nums, int n)
    {
        // using bit manipulation
        for (int i = n; i < 2 * n; i++)
        {
            nums[i] <<= 10;         // left-shiting by 10 bits
            nums[i] |= nums[i - n]; // adding the corresponding lower half part to it
        }
        int z = n; // z is the index of the first element of the second half
        for (int i = 0; i < 2 * n; i += 2)
        {
            nums[i] = nums[z] & 1023;      // extracting the lower half part
            nums[i + 1] = nums[z++] >> 10; // extracting the upper half part
        }
        return nums;
    }
};
int main()
{
}