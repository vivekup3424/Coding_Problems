#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &adj, vector<long long> bribes, vector<bool> &visited, int start, long long &minValue)
{
    if (visited[start])
        return;

    visited[start] = true;
    minValue = min(minValue, bribes[start]);

    for (auto child : adj[start])
    {
        dfs(adj, bribes, visited, child, minValue);
    }
}

int main()
{
    int n, m; // n = nodes, m = vertices
    cin >> n >> m;
    vector<long long> bribes(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> bribes[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<bool> visited(n + 1, false);
    vector<long long> values;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            long long minValue = INT_MAX;
            dfs(adj, bribes, visited, i, minValue);
            values.push_back(minValue);
        }
    }

    long long sum = 0;
    for (int i : values)
    {
        sum += i;
    }
    cout << sum << endl;

    return 0;
}
