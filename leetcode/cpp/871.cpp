#include <bits/stdc++.h>
using namespace std;
auto compare = [](const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second; // max-heap larger fuel comes first
};
class Solution
{
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
    {
        int n = stations.size();
        int prevPosition = 0;
        int leftOutFuel = startFuel;
        int range = startFuel;
        sort(stations.begin(), stations.end());
        int i = 0; // station index
        int refuels = 0;
        while (range < target)
        {
            priority_queue<pair<int, int>,
                           vector<pair<int, int>,
                                  decltype(compare)>>
                pq;
            while (i < n and stations[i][0] <= range)
            {
                pq.push({stations[i][0], stations[i][1]});
            }
            // get the first fuel
            auto p = pq.top();
            delete (&pq);
        }
    }
};
