
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> nums = {1, 3, 8, 5, 3, 1, 8, 8};
    Solution *A = new Solution();
    printVector(A->distinctDifferenceArray(nums)); // (0, 1, 2, 1, 1, 0, 0, 0
}
void printVector(vector<int> nums)
{
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;
};
void printSet(unordered_set<int> s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        cout << *it << " ";
    cout << endl;
};
class Solution
{
public:
    vector<int> distinctDifferenceArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> diff(n);
        unordered_set<int> prefix, suffix;

        // calculate the number of distinct elements in the suffix from i+1 to n-1
        diff[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            suffix.insert(nums[i + 1]);
            diff[i] = suffix.size();
        }

        // calculate the number of distinct elements in the prefix from 0 to i
        for (int i = 0; i < n; i++)
        {
            prefix.insert(nums[i]);
            diff[i] -= prefix.size();
            diff[i] = -diff[i];
        }

        return diff;
    }
};