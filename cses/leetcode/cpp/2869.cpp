
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minOperations(vector<int> &nums, int k)
    {
        set<int> s;
        int moves = 0;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            moves++;
            if (nums[i] <= k)
            {
                s.insert(nums[i]);
            }
            if (s.size() == k)
                return moves;
        }
        return 0;
    }
};
int main()
{
}