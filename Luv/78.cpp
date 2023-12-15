
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
vector<int> g[N]; // adjacency list
bool visited[N] = {false};
queue<int> q;
void bfs(int src)
{
    if (visited[src])
        return;
    q.push(src);
    visited[src] = true;
    while (q.empty() != false) // while queue is not empty
    {
        int temp = q.front();
        q.pop();
        for (auto child : g[temp])
        {
            if (visited[child] != false)
            {
                q.push(child);
                visited[child] = true;
            }
        }
    }
    // Time Complexity = O(V+E) , important question Why is the time-complexity = O(V+E)
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}