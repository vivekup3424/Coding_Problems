#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void outputVector(vector<int> v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}
// make a graph
map<int, vector<int>> makeGraph(vector<vector<int>> edges)
{
    map<int, vector<int>> graph;
    for (auto e : edges)
    {
        int a = e[0], b = e[1];
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    // print out the graph
    for (auto it : graph)
    {
        std::cout << it.first << "=>";
        outputVector(it.second);
    }
}

int main()
{
    // make graphs with : edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
    edge1 = { {0, 1},
    }
}