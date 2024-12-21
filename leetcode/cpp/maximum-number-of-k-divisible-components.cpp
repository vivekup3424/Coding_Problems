#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int dfs(map<int, set<int>> &graph, vector<int> &values, int source, set<int> &visited, int k, int &count)
    {
        if (visited.count(source))
        {
            return 0;
        }
        visited.insert(source);
        int totalSubTreeValue = 0;
        for (auto neighbor : graph[source])
        {
            totalSubTreeValue += dfs(graph, values, neighbor, visited,k,count);
        }
        totalSubTreeValue += values[source];
        // printf("Sum of subtree with root(%d) is %d\n", source, totalSubTreeValue);
        if (totalSubTreeValue % k == 0)
        {
            count++;
            return 0;
        }
        return totalSubTreeValue;
    }
    int maxKDivisibleComponents(int n, vector<vector<int>> &edges, vector<int> &values, int k)
    {
        // first let's construct the graph
        map<int, set<int>> graph;
        for (auto edge : edges)
        {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        //print out the graph
        for (auto it : graph)
        {
            // cout << "Node " << it.first << " has neighbors: ";
            for (auto neighbor : it.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        set<int> visited;
        int count = 0;
        dfs(graph,values,0,visited,k,count);
        return count;
    }
};
int main(){
    int n = 5;
    vector<vector<int>> edges = {{0, 2}, {1, 2}, {1, 3}, {2, 4}};
    vector<int> values = {1, 8, 1, 4, 4};
    int k = 6;

    Solution solution;
    int result = solution.maxKDivisibleComponents(n, edges, values, k);

    // cout << "Output: " << result << endl;
    return 0;
}