#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class DSU
{
public:
    vector<int> parents;
    vector<int> sizes;
    int num_components;
    DSU(int size) : parents(size), sizes(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parents[i] = i;
            num_components++;
        }
    }
    int find(int x)
    {
        return parents[x] == x ? x : parents[x] = (find(parents[x]));
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
        num_components--;
        return true;
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};
int main()
{
    ll n, m; // vertices,edges
    cin >> n >> m;
    // make the dsu now
    DSU d(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<bool> ans;
    for (int i = 0; i < n; i++)
    {
        ll a;
        cin >> a;
    }
}