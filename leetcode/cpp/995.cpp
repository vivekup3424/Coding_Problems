#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minKBitFlips(vector<int> &nums, int k)
    {
        int count = 0;
        int n = nums.size();
        for (int i = 0; i <= n - k; i++)
        {
            if (nums[i] == 0)
            {
                count++;
                for (int j = 0; j < k; j++)
                {
                    if (nums[i + j] == 0)
                        nums[i + j] = 1;
                    else if (nums[i + j] == 1)
                    {
                        nums[i + j] = 0;
                    }
                }
            }
        }
        // check if zero-exists somewhere
        bool flag = true;
        for (int i : nums)
        {
            if (i == 0)
            {
                flag = false;
                break;
            }
        }
        if (flag == false)
        {
            cout << -1 << endl;
            return -1;
        }
        else
        {
            cout << count << endl;
            return count;
        }
    }
};