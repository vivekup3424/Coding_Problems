// How to DFS in a TREE | Height and Depth of a TREE | CP Course | EP 73

// since there is no cycle in the vertex.
// we dont need a visited array, we can prevent the cycle by
// just passing the parent node in the function
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
int depth[N], height[N];
void dfs(int vertex, int parent = 0)
{
    for (auto child : g[N])
    {
        // take action on the child before visiting it
        depth[child] = depth[vertex] + 1;
        if (child == parent)
            continue;
        dfs(child, vertex);
        // take action on the child after exiting it
        height[vertex] = max(height[vertex], height[child] + 1);
    }
}
int main()
{
    int n; // no of nodes
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
}