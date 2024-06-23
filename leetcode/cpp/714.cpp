#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        int free[n + 1], hold[n + 1];
        free[0] = 0, hold[0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            // hold[i] = free[i-1]-price[i]; //day i, buy
            // free[i] = hold[i-1]+price[i]-free //sell
            // free[i] = free[i-1] //doing nothing
            // hold[i] = hold[i-1] //doing nothing

            // this implies
            free[i] = max(free[i - 1], hold[i - 1] + prices - fee);
            hold[i] = max(hold[i - 1], free[i - 1] - prices[i]);
        }
        return free[n - 1];
    }
    // we are making two arrays because there are two
    // independent constraints here
};
int main()
{
    
}