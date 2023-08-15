// How to find Connected Components and Cycle in a Graph using DFS | CP Course | EP 71

// undirected graph

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
vector<int> adj[N];                                                                   // adj list to represent graph
void dfs(int source, bool visited[], int N, vector<int> current_connected_components) // N = number of vertices
{
    visited[source] = true;
    current_connected_components.push_back(source);
    for (auto child : adj[source])
    {
        if (visited[child] == true)
            continue; // skip
        dfs(child, visited, N, current_connected_components);
    }
}
void printMatrix(vector<vector<int>> cc)
{
    for (auto c : cc)
    {
        for (auto vertex : c)
        {
            cout << vertex << ",";
        }
        cout << "\n";
    }
}
int main()
{
    int n, e; // n = number of vertices, e = num of edges
    cin >> n >> e;
    for (int i = 0; i < e; i++) // undirected graph
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int count = 0; // counter for connected components
    bool visited[n];
    vector<vector<int>> connected_components; // stores in the set of connected components
    vector<int> current_connected_components; // stores current set of connected components
    memset(visited, false, n);
    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        current_connected_components.clear(); // empty the list of connected components
        dfs(i, visited, n, current_connected_components);
        connected_components.push_back(current_connected_components);
        count++;
    }
    cout << count << "\n";
    printMatrix(connected_components);
    return 0;
}

// now next question, finding cycle in the graph
bool detectCycle(int source, int parent, bool visited[], int N) // N = number of vertices
{
    visited[source] = true;
    bool isLoopPresent = false;
    for (auto child : adj[source])
    {
        if (visited[child] and child == parent)
            continue;
        if (visited[child] == true)
            return true; // skip
        isLoopPresent = (isLoopPresent or detectCycle(child, source, visited, N));
    }
}
int main1()
{
    int n, e; // n = number of vertices, e = num of edges
    cin >> n >> e;
    for (int i = 0; i < e; i++) // undirected graph
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    bool visited[n];
    memset(visited, false, n);
    bool isLoopPresent = false;
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue;
        if (detectCycle(i, 0, visited, n))
        {
            isLoopPresent = true;
            break;
        }
    }
    cout << isLoopPresent << "\n";
}