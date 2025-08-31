#include <bits/stdc++.h>
using namespace std;
#define MAX 100
bool visited[MAX];
bool dfsUtilCycleCheck(int s, vector<int, char> adj[], int parent)
{
    if (visited[s])
        return false;
    visited[s] = true;
    for (auto u : adj[s])
    {
        if (visited[u] and u != parent)
            return true;
        dfsUtilCycleCheck(u, adj, s);
    }
}
bool dfs(vector<int> adj[], int N)
{
    bool result = false;
    for (auto i = 1; i <= N; i++)
    {
        result = dfsUtilCycleCheck(i, adj, 0);
        if (result)
            break;
    }
    return result;
}
int main()
{
    int N;
    cin >> N;
    vector<pair<int, char>> adj[N + 1];
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(pair<int, char>(b, 'W'));
        adj[b].push_back(pair<int, char>(a, 'W'));
    }
    bool result = dfs(adj, N);
    cout << result << endl;
}