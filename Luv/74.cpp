#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
/**Pre-Computation using DFS | Subtree Queries | Tree given as connected acyclic graph
 * Given Q queries, Q <= 10^5
 * In each query given V,
 * Print the subtree sum of V, and
 * count of number of even nodes in V
 */

int subtreeSum[N];
int evenCount[N];
vector<int> g[N];
void dfs(int src, int parent = 0)
{
    subtreeSum[src] += src;
    if (src & 1 == 0) // even
    {
        evenCount[src]++;
    }
    for (auto child : g[N])
    {
        if (child == parent)
            continue;
        dfs(child);
        subtreeSum[src] += child;
        if (child & 1 == 0) // even
        {
            evenCount[src]++;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        // input the edge list of the tree
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
}