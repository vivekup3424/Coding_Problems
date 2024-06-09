/**
 *There are n cities and m flight connections between them. Your task
 is to determine the length of the shortest route from Syrjälä to every city.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    vector<int> distances(n, INT_MAX);
    distances[0] = 0;
    minHeap.push({0, 0});
    while (minHeap.size() > 0)
    {
        int node = minHeap.top().second;
        int weight = minHeap.top().first;
        minHeap.pop();
        for (auto a : adj[node])
        {
            int edgeWeight = a.second;
            int adjNode = a.first;
            int pathLength = weight + edgeWeight;
            if (pathLength < distances[adjNode])
            {
                distances[adjNode] = pathLength;
                minHeap.push({pathLength, adjNode});
            }
        }
    }
    // print out the shortest paths
    for (auto w : distances)
    {
        cout << w << " ";
    }
    cout << endl;
}