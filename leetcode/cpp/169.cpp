
#include <bits/stdc++.h>
using namespace std;
int majorityNumber(int arr[], int n) // using map Method 1
{
    int ans = -1;
    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]++;
        if (freq[arr[i]] > n / 2)
            ans = arr[i];
    }
    return ans;
    // Complexity Analysis:
    // Time Complexity : O(n)
    // Auxiliary Space : O(n)
}
// Method 2
// Boyer-Moore Algorithm
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int count = 1, res = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (count == 0)
                res = nums[i];
            nums[i] == res ? count++ : count--;
        }
        return res;
    };
};

int main()
{
}