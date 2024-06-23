
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    const int mod = 1e9 + 7;
    int bits = 31;

    int maxSum(vector<int> &nums, int k)
    {
        int ans = 0;
        int barr[bits];
        for (int i = 0; i < bits; i++)
            barr[bits] = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            int x = nums[i];
            int j = 0;
            while (x)
            {
                if (x & 1)
                {
                    barr[j++]++;
                }
                x >= 1;
            }
        }

        for (int i = 0; i < k; i++)
        {
            int sum = 0;
            for (int j = 0; j < bits; j++)
            {
                if (barr[j] > 1)
                {
                    sum = (sum + pow(2, j));
                    barr[j]--;
                }
            }
            int y = (sum % mod * sum % mod) % mod;
            ans = ((ans % mod) + (y % mod)) % mod;
        }
        return ans % mod;
    }
};
int main()
{
}