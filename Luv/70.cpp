// writing DFS in a good way

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

// input the graph as adj list
vector<int> adj[N]; // N = no of vertices

void dfs(int source); // source node
int main()
{
    int n, m;
    cin >> n >> m; // n = no of vertices,m = no of edges
    for (auto i = 0; i < m; i++)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        adj[vertex1].push_back(vertex2);
        adj[vertex2].push_back(vertex1);
    }
}

bool visited[N];

// now implementing the dfs function
// basic structure of dfs
void dfs(int source)
{
    // taking action on source after entering the source
    for (auto child : adj[source])
    {
        // taking action on child before entering the child
        dfs(child);
        // taking action on child after exiting the child
    }
    // taking action on source before exiting the source
}
void dfs(int source)
{
    cout << source << " ,";
    visited[source] = true;
    for (auto child : adj[source])
    {
        if (visited[child])
            continue;
        dfs(child);
    }
}