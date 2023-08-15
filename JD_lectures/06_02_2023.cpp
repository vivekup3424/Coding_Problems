// shortest path algo
#define INF __INT_MAX__
#include <bits/stdc++.h>
// 1. Floyd-Warshall Algo
// it finds shortest
// paths between all node pairs of the graph in a single run.
// few lines of code only

// D0
/*
0 2 3 INF INF
2 0 INF 5 INF
3 INF 0 4 INF
INF 5 4 0 1
INF INF INF 1 0
*/

// D1 (choosing 1 as intermediate node)
// The algorithm continues like this, until all nodes have been appointed intermediate
// nodes. After the algorithm has finished, the matrix contains the minimum distances
// between any two nodes:

// algo is easy to implement
// 1. represent the graph in adj matrix form

// dist[a][b] denotes the shortest distance between nodes a and b.
// First, the algorithm initializes dist using the adjacency matrix adj of the graph:
for (int i = 1; i <= n; i++) // n = number of vertices
{
    // D0
    for (int j = 1; j <= n; i++)
    {
        if (i == j)
            dist[i][j] == 0;
        else if (adj[i][j])
            dist[i][j] = adj[i][j];
        else
            dist[i][j] = INF
    }
}
// O(n^2)

for (int k = 1; k <= n; k++) // intermediate node
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        }
    }
}

// 2. Bellman-ford algo
int distance[100] for (int i = 1; i <= n; i++)
{
    distance[i] = INF; // relative to source node
}
distance[x] = 0; // x = source node
for (int i = 1; i <= n - 1; i++)
{
    for (auto e : edges)
    {
        int a, b, w;
        tie(a, b, w) = e;
        distance[b] = min(distance[b], distance[a] + w);
    }
}