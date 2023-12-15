// 189. Rotate Array

#include <bits/stdc++.h>
using namespace std;
class Solution1
{
    // using modulus operator and O(n) extra space
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
    // most optimal solution
    // reverse the right part and left part and then reverse whole , single pass algo
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