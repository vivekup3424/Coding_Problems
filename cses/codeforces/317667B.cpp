#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9+7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
void dfs(vvll &adj, vll &cost, vector<bool> &visited, ll src, ll &minCost)
{
    if (visited[src])
    {
        return;
    }
    else
    {
        visited[src] = true; // Changed from '==' to '='
        minCost = min(minCost, cost[src]);
        for (auto child : adj[src])
        {
            dfs(adj, cost, visited, child, minCost);
        }
    }
}

int main()
{
    fast_io();
    ll n, m;
    cin >> n >> m;
    vll cost(n);
    inputVector(cost, n);
    vvll graph(n);
    while (m--)
    {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<bool> visited(n, false);
    ll sumTotal = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
        {
            ll minCost = LLONG_MAX;
            dfs(graph, cost, visited, i, minCost);
            sumTotal += minCost;
        }
    }
    cout << sumTotal << endl;
}