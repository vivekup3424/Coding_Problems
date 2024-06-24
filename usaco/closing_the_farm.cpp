#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll vertices, edges;
    cin >> vertices >> edges;
    // creating an adjacency list
    vector<vector<int>> adj(vertices);
    for (int i = 0; i < edges; i++)
    {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}