#include <iostream>
#include <vector>
#include <limits>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // Initialize distances array with INF
        vector<int> dist(n, INT_MAX);
        dist[0] = 0; // Starting node
        
        // Relax edges repeatedly
        for (int i = 0; i < n - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge[0], v = edge[1], w = edge[2];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        // Check for negative weight cycles
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                // Negative weight cycle detected
                return vector<int>(n, -1);
            }
        }
        
        // Adjust times based on disappear times
        for (int i = 0; i < n; ++i) {
            if (disappear[i] < dist[i]) {
                dist[i] = -1; // Node disappears before it can be reached
            }
        }
        
        return dist;
    }
};

int main() {
    Solution sol;

    // Test case
    int n = 1;
    vector<vector<int>> edges = {{0,0,4},{0,0,2},{0,0,7},{0,0,8},{0,0,10},{0,0,4},{0,0,6},{0,0,10},{0,0,3},{0,0,1}};
    vector<int> disappear = {19};

    vector<int> result = sol.minimumTime(n, edges, disappear);

    cout << "Minimum times to reach each node:\n";
    for (int i = 0; i < result.size(); ++i) {
        cout << "Node " << i << ": " << result[i] << endl;
    }

    return 0;
}
