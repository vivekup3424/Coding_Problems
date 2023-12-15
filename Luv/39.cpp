// Subset Generation using Recursion and backtracking | CP Course | EP 39

// Given an integer array nums of unique elements, return all possible subsets
//  The solution must not contain duplicate subsets. Return the solution in any order.

// Example 1

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> subsets;
void generate(vector<int> &subset, int i, vector<int> &nums) // wether to choose the ith index element or not
{
    if (i == nums.size())
    {
        subsets.push_back(subset);
        return;
    }
    // not choosing
    generate(subset, i + 1, nums);

    // choosing the ith element in the subset vector
    subset.push_back(nums[i]);
    generate(subset, i + 1, nums);
    subset.pop_back(); // this is the backtracking step
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        nums[i] = temp;
    }
    vector<int> empty;
    generate(empty, 0, nums);
    for (auto subset : subsets)
    {
        for (auto element : subset)
        {
            cout << element << ", ";
        }
        cout << "\n";
    }
}