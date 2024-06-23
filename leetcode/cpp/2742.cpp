
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int paintWalls(vector<int> &cost, vector<int> &time)
    {
        int n = cost.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < n; i++)
        {
            idx[cost[i]] = i;
        }
        sort(cost.begin(), cost.end());
        int total = 0;
        for (int i = 0; i < n / 2; i++)
        {
            total += cost[i];
        }
        return total;
    }
};
int main()
{
}