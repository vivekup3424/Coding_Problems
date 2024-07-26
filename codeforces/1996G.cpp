#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Function to find the root of a node in the union-find structure
int find(int node, vector<int> &parent)
{
    if (parent[node] != node)
    {
        parent[node] = find(parent[node], parent); // Path compression
    }
    return parent[node];
}

// Function to unite two sets in the union-find structure
void union_sets(int a, int b, vector<int> &parent, vector<int> &rank)
{
    int rootA = find(a, parent);
    int rootB = find(b, parent);

    if (rootA != rootB)
    {
        if (rank[rootA] < rank[rootB])
        {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        if (rank[rootA] == rank[rootB])
        {
            rank[rootA]++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<int> parent(n + 1), rank(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
        }

        vector<pair<int, int>> friendships(m);
        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            friendships[i] = {a, b};
            union_sets(a, b, parent, rank);
        }

        unordered_set<int> component_leaders;
        for (int i = 1; i <= n; ++i)
        {
            component_leaders.insert(find(i, parent));
        }

        int num_components = component_leaders.size();

        int min_roads = max(num_components, 1);

        cout << min_roads << endl;
    }

    return 0;
}
