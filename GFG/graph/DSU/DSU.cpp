#include <bits/stdc++.h>
using namespace std;
/**
 * iota is a function in the C++ Standard Library, specifically from the 
 * <numeric> header. It is used to fill a range of elements with 
 * sequentially increasing values, starting from a specified initial value.
Syntax:

cpp

iota(start, end, initial_value);
 * */
class DSU {
private:
    vector<int> parent, size;

public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        if (parent[a] != a) 
            parent[a] = find(parent[a]); // Path compression
        return parent[a];
    }

    void unionNodes(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU == rootV) return;

        // Union by size
        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
};
