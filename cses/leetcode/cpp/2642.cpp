#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Graph
{
public:
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> distanceMatrix;
    int vertices;

    Graph(int n, vector<vector<int>> &edges)
    {
        vertices = n;
        adj.resize(n);
        distanceMatrix.resize(n, vector<int>(n, INT_MAX));

        // Initialize diagonal to zero (distance to self is zero)
        for (int i = 0; i < n; ++i)
        {
            distanceMatrix[i][i] = 0;
        }

        // Add edges to adjacency list
        for (auto edge : edges)
        {
            int a = edge[0], b = edge[1], w = edge[2];
            adj[a].push_back({b, w});
        }
    }

    void addEdge(vector<int> edge)
    {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    int shortestPath(int node1, int node2)
    {
        if (distanceMatrix[node1][node2] != INT_MAX || node1 == node2)
        {
            return distanceMatrix[node1][node2];
        }

        // Priority queue for Dijkstra's algorithm
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Vector to store the shortest distances
        vector<int> distances(vertices, INT_MAX);
        distances[node1] = 0;
        pq.push({0, node1});

        // Dijkstra's algorithm
        while (!pq.empty())
        {
            int node = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            for (auto it : adj[node])
            {
                int neighbor = it.first;
                int distance = dist + it.second;

                if (distance < distances[neighbor])
                {
                    distances[neighbor] = distance;
                    pq.push({distance, neighbor});
                }
            }
        }

        // Fill up the matrix-row for node1 row-index
        for (int i = 0; i < vertices; i++)
        {
            distanceMatrix[node1][i] = distances[i];
        }

        return distanceMatrix[node1][node2];
    }
};

int main()
{
    vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 1}, {2, 1, 2}, {1, 3, 1}, {2, 3, 5}};
    Graph g(4, edges);
    g.addEdge({3, 0, 1});
    cout << g.shortestPath(0, 3) << endl; // Example usage
    return 0;
}
