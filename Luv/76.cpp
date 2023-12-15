// How to find Lowest Common Ancestor(LCA) in a Tree | CP Course | EP 76

// Doing this problem in O(n) approach

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> adj[N];
int parents[N]; // stores the parent of the ith node
void dfs(int v, int parent = 0)
{
    parents[v] = parent;
    for (auto child : adj[v])
    {
        if (child == parent)
            continue;
        dfs(child, v);
    }
}
vector<int> path(int v)
{
    /// root = 1
    vector<int> ans;
    while (v != 0)
    {
        ans.push_back(v);
        v = parents[v];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int LCA(int x, int y)
{
    dfs(1, 0);
    vector<int> pathx = path(x);
    vector<int> pathy = path(y);
    int min_l = min(pathx.size(), pathy.size());
    for (auto i = 0; i < min_l; i++)
    {
        if (pathx[i] == pathy[i])
            return pathy[i];
    }
    return 0;
}
int main()
{
    int n, m; // n = vertices,m=edges
    cin >> n;
    for (auto i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int l = LCA(3, 4);
    cout << l << endl;
    return 0;
}