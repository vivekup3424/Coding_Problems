
#include <bits/stdc++.h>
using namespace std;
// this is the most stupid code I have written, with no idea of what the fuck is going
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        // starting at index 0
        int n = cost.size();
        int dp0[n], dp1[n];
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                dp0[i] = cost[i];
            else if (i == 1)
                dp0[i] = cost[i] + dp0[i - 1];
            else
            {
                if (i == n - 1)
                    dp0[i] = min(dp0[i - 1], dp0[i - 2]);
                else
                    dp0[i] = min(dp0[i - 1], dp0[i - 2]) + cost[i];
            }
        };
        // starting at the index 1
        for (int i = 1; i < n; i++)
        {
            if (i == 1)
                dp1[i] = cost[i];
            else if (i == 2)
                dp1[i] = cost[i] + dp1[i - 1];
            else
            {
                if (i == n - 1)
                    dp1[i] = min(dp1[i - 1], dp1[i - 2]);
                else
                    dp1[i] = min(dp1[i - 1], dp1[i - 2]) + cost[i];
            }
        }
        return min(dp0[n - 1], dp1[n - 1]);
    }
};
int main()
{
    // Test the minCostClimbingStairs function
    Solution obj;
    vector<int> cost = {10, 15, 20};

    int minCost = obj.minCostClimbingStairs(cost);

    cout << "Minimum cost to climb stairs: " << minCost << endl;

    return 0;
}