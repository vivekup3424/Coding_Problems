
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    // brute force
    int countKDifference(vector<int> &nums, int k)
    {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (abs(nums[i] - nums[j]) == k)
                    ans++;
            }
        }
        return ans;
    }
    // Time complexity: O(n^2)
    // Space complexity: O(1)
};
// using hashmap
class Solution
{
public:
    int minSteps(string s, string t)
    {
        unordered_map<char, int> m;
        int sum = 0;
        for (auto i : s)
            m[i]++;
        for (auto i : t)
            m[i]--;
        for (auto i : m)
        {
            if (i.second < 0)
                sum += i.second;
        }
        return abs(sum);
    }
};
int main()
{
}