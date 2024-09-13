#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
    {
        int n = stations.size();
        int prevPosition = 0;
        // as a start let's find some kind of count
        for (int i = 0; i < n; i++)
        {
            int place = stations[i][0];
            int fuel = stations[i][1];
            startFuel -= place - prevPosition + fuel;
            if (startFuel < 0)
            {
                return -1;
            }
            else if (startFuel == 0 and place != target)
            {
                return -1;
            }
        }
    }
};
