#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> parent, size;
public:
    DSU(int n) {
        size.resize(n + 1, 1);  // Using 1-based indexing
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int a) { // Path compression
        if (parent[a] != a) {
            parent[a] = find(parent[a]);
        }
        return parent[a];
    }

    bool unionNodes(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) return false; // This edge creates a cycle (redundant)
        
        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DSU dsu(n);
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (!dsu.unionNodes(u, v)) {
                return edge; // The first edge that forms a cycle is the redundant one
            }
        }
        return {};
    }
};
