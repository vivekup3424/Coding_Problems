
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        // Method 1 : Using Sorting and checking for smallest missing positive integer
        // Time Complexity = O(nlogn)
        // Space Complexity = O(1)

        // Method 2: Using a container data structure
        // T  = O(n)
        // S = O(n)

        // Method 3: Unknown
        // Maximum number of elements = n
        // Largest smallest number = n+1
        // Take a visited vector of size n+1
        // Time Complexity = O(n)
        // Space Complexity = O(1
        // Or make use of original nums as visited vector
        // use two pointer approach to sort the array
        int n = nums.size();
        int currentSmallest = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1 and nums[i] <= n and nums[i] > 0)
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1 and nums[i] <= n and nums[i] > 0)
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            cout << i << "=>" << nums[i] << endl;
            if (nums[i] != i + 1)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};
int firstMissingPositiveSort(vector<int> nums)
{
    sort(nums.begin(), nums.end());
    int ans = 1;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == ans)
        {
            ans++;
        }
    }
    return ans;
}
int main()
{
    vector<int> v = {3, 4, -1, 1};
    Solution *A = new Solution();
    A->firstMissingPositive(v);
}