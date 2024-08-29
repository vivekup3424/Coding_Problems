#include <bits/stdc++.h>
using namespace std;
struct point
{
    int x;
    int y;
};
class Solution
{
public:
    int removeStones(vector<vector<int>> &stones)
    {
        int currentStone = 0;
        unordered_map<int, point> mp;
        for (auto v : stones)
        {
            point p = {v[0], v[1]};
            mp[currentStone++] = p;
        }
        vector<vector<int>> adj(currentStone);
        for (int i = 0; i < n; i++)
        {
        }
    }
};