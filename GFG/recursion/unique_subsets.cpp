//`Adtiya Verma
// Print unique subsets And Variations

// Given an array arr[] of integers of size N that might contain duplicates,
// the task is to find all possible unique subsets.
//
// Note: Each subset should be sorted.
//
// Example 1:
//
// Input: N = 3, arr[] = {2,1,2}
// Output:(),(1),(1 2),(1 2 2),(2),(2 2)

#include <bits/stdc++.h>
using namespace std;
set<vector<int>> unique_subsets;
void generate_subsets(vector<int> &subset, int i, vector<int> &nums) // this uses set
{
    if (i == nums.size())
    {
        unique_subsets.insert(subset);
        return;
    }
    subset.push_back(nums[i]);
    generate_subsets(subset, i + 1, nums);
    subset.pop_back();
    generate_subsets(subset, i + 1, nums);
}
int main()
{
    vector<int> nums = {2, 1, 2};
    vector<int> empty;
    generate_subsets(empty, 0, nums);
    for (auto subset : unique_subsets)
    {
        for (auto element : subset)
        {
            cout << element << ", ";
        }
        cout << "\n";
    }
}