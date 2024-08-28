#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool validTree(int n, vector<vector<int>> &edges)
    {
        if (edges.size() != n - 1)
        {
            return false;
        }
        vector<vector<int>> graph(n);
        for (auto edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
        }
    }
};
