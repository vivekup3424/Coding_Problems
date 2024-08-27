/*
Count Connected Components

There is an undirected graph with n nodes. There is also an edges array, where edges[i] = [a, b] means that there is an edge between node a and node b in the graph.

The nodes are numbered from 0 to n - 1.

Return the total number of connected components in that graph.
*/

#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    int vertices;
    vector<int> parents;
    vector<int> size;
    DSU(int v)
    {
        vertices = v;
        parents.resize(vertices);
        for (int i = 0; i < vertices; i++)
        {
            parents[i] = i;
        }
        size.resize(vertices);
        for (int i = 0; i < vertices; i++)
        {
            size[i] = 1;
        }
    }
    int find(int a)
    {
        if (parents[a] != a)
        {
            parents[a] = find(parents[a]);
        }
        return parents[a];
    }
    void Union(int u, int v)
    {
        int parent_u = find(u);
        int parent_v = find(v);
        if (parent_u == parent_v)
        {
            return;
        }
        else if (size[parent_u] < size[parent_v])
        {
            parents[parent_u] = parent_v;
            size[parent_v] += size[parent_u];
        }
        else
        {
            parents[parent_v] = parent_u;
            size[parent_u] += size[parent_v];
        }
    }
    int countComponents()
    {
        int count = 0;
        for (int i = 0; i < vertices; i++)
        {
            if (i == parents[i])
            {
                count++;
            }
        }
        return count;
    }
};

int countComponents(int n, vector<vector<int>> &edges)
{
    auto d = new DSU(n);
    for (auto edge : edges)
    {
        d->Union(edge[0], edge[1]);
    }
    return d->countComponents();
}