#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double ans;
    double mn = 1e-5;
    void f(vector<pair<int, double>> adj[], int node, int end, double sum, vector<int> &vis)
    {
        if (sum <= mn)
            return;
        if (node == end)
        {
            ans = max(ans, sum);
            return;
        }
        vis[node] = 1;
        for (auto it : adj[node])
        {
            if (!vis[it.first] && (sum * it.second) >= ans)
                f(adj, it.first, end, sum * it.second, vis);
        }
        vis[node] = 0;
    }
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end)
    {
        vector<pair<int, double>> adj[n];
        int i = 0;
        for (auto edge : edges)
        {
            adj[edge[0]].push_back({edge[1], succProb[i]});
            adj[edge[1]].push_back({edge[0], succProb[i]});
            i++;
        }
        vector<int> vis(n, 0);
        ans = 0;
        f(adj, start, end, 1, vis);
        return ans;
    }
};