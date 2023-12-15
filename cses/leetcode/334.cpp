// we can find three elements in lexographical increasing order
#include <bits/stdc++.h>
using namespace std;
// let's think of a bruteforce solution first
class Solution1
{
public:
    bool increasingTriplet(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] > nums[i])
                {
                    for (int k = j + 1; k < n; k++)
                    {
                        if (nums[k] > nums[j])
                            return true;
                    }
                }
            }
        }
        return false;
    }
    // Time complexity = O(n^3)
    // Space complexity = o(1)
};
// yeah so the above bruteforce solution is correct, now let's think of someway
// to optimize it

// I think I can optimize it using a greedy approach, like
// suppose for each element, I keep an minimum and maximum array for all the elements of the array
// I will check for any particular index whether min[i]<i<max[i]

class Solution2
{
public:
    bool increasingTriplet(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> Min(n), Max(n, -1);
        for (int i = 0; i < nums.size(); i++)
        {
            if (i == 0)
            {
                Min[i] = i;
            }
            else
            {
                Min[i] = min(i, Min[i - 1]);
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == n - 1)
            {
                Max[i] = i;
            }
            else
            {
                Max[i] = max(i, Max[i + 1]);
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (Min[i] < i and i < Max[i])
            {
                return true;
            }
        }
        return false;
    }
};
// yeah so it seems the above approach is bullshit, unnecessarily complecating things
// so I think the problem should be smaller if we can find three elements in lexographical increasing order
int main()
{
}