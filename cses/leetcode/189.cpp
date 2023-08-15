// 189. Rotate Array

#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    void rotate(vector<int> &nums, int k)
    {
        // Method -1: Using O(n) space
        int n = nums.size();
        vector<int> res(n);
        for (int i = 0; i < n; i++)
        {
            int a = (i + k) % n;
            res[a] = nums[i];
        }
        swap(nums, res);
    }
};
class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        // using constant space
        k %= nums.size();
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }

private:
    void reverse(vector<int> &nums, int l, int r)
    {
        while (l < r)
            swap(nums[l++], nums[r--]);
    }
};
int main()
{
}