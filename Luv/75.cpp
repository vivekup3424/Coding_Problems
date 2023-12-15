/**How to find the diameter of a tree
 * 1. With any node as root, find the node A having maximum depth
 * 2. From this node A, find any node having maximum depth.
 * 3. Hence you get the depth, use DFS for finding depth.
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> G[N];
int depth[N];
void dfs(int vertex, int parent = 0)
{
    for (auto child : G[vertex])
    {
        // take action of child before visting it
        depth[child] = depth[vertex] + 1;
        if (child == parent)
        {
            continue;
        }
        dfs(child, vertex);
    }
}
int main()
{
    int n; // no of nodes
    cin >> n;
    // now input the edgeList
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // let root be 1
    int vertex = 1;
    dfs(vertex);
    int max_depth = -1, max_depth_node = -1;
    for (int i = 1; i <= n; i++)
    {
        if (depth[i] > max_depth)
        {
            max_depth = depth[i];
            max_depth_node = i;
        }
        depth[i] = 0; // resetting the depth array
    }

    dfs(max_depth_node);
    // now find the maximum depth again.
}