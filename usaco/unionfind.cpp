#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class DSU
{
public:
    int vertices;
    std::vector<int> parent;
    std::vector<int> rank;

    // Constructor initializes the DSU with n vertices
    DSU(int n)
    {
        vertices = n;
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Find function with path compression
    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Union function with union by rank
    void union_sets(int u, int v)
    {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v)
        {
            if (rank[root_u] < rank[root_v])
            {
                parent[root_u] = root_v;
            }
            else if (rank[root_u] > rank[root_v])
            {
                parent[root_v] = root_u;
            }
            else
            {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

int main()
{
    ll n, q;
    cin >> n >> q;
    DSU d(n);
    while (q--)
    {
        ll a, v, u;
        cin >> a >> v >> u;
        if (a == 0)
        {
            d.union_sets(v, u);
        }
        else if (a == 1)
        {
            if (d.parent[v] == d.parent[u])
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
}
class DSU
{
public:
    vector<int> parents;
    vector<int> sizes;
    DSU(int size) : parents(size), sizes(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parents[i] = i;
        }
    }
    int find(int x)
    {
        return parents[x] == x ? x : (parents[x] = find(parents[x]));
    }
    bool unite(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root)
        {
            return false;
        }

        if (sizes[x_root] < sizes[y_root])
        {
            swap(x_root, y_root);
        }
        sizes[x_root] += sizes[y_root];
        parents[y_root] = x_root;
        return true;
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};
