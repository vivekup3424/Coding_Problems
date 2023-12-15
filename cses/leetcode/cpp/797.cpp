
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void dfs(vector<vector<int>> &graph, int src, vector<int> &visited, vector<int> &path, vector<vector<int>> &ans)
    {
        path.push_back(src);
        visited[src] = 1;

        if (src == graph.size() - 1)
        {
            ans.push_back(path);
            return;
        }
        else
        {
            for (auto child : graph[src])
            {
                dfs(graph, child, visited, path, ans);
                path.pop_back(); // Backtrack after each recursive call
            }
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        vector<vector<int>> ans;
        vector<int> visited(graph.size(), 0);
        vector<int> path;
        dfs(graph, 0, visited, path, ans);
        return ans;
    }
};
int main()
{
}