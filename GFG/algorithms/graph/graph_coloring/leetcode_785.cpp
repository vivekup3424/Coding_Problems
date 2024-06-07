#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    void color_graph(vector<vector<int>> graph) bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, -1);
        for (int i = 0; i < n; i++)
        {
            if (colors[i] == -1)
            {
                color_graph(graph, i, colors, 0)
            }
        }
    }
};