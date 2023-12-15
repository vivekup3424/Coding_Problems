
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minimumSemesters(int N, vector<vector<int>> relations)
    {
        vector<int> indegree(N, 0);
        vector<vector<int>> adj(N);
        for (auto r : relations)
        {
            adj[r[0]].push_back(r[1]); // creating a directed graph
            indegree[r[1]]++;
        }
    }
};
int main()
{
}