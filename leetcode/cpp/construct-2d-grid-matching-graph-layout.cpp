#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(n);
        map<int, int> degrees(n, 0;
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            degrees[u]++;
            degrees[v]++;
        }
    }
};
