#include <bits/stdc++.h>
using namespace std;

struct coordinate
{
    int x;
    int y;
};

int solution(int n, vector<vector<int>> entryTime)
{
    priority_queue<pair<int, coordinate>, vector<pair<int, coordinate>>, greater<pair<int, coordinate>>> pq;
    pq.push({0, {0, 0}}); // Start with time = 0 at position (0, 0)

    vector<vector<int>> visited(n, vector<int>(n, INT_MAX));
    visited[0][0] = 0;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!pq.empty())
    {
        auto [currentTime, coord] = pq.top();
        pq.pop();

        int x = coord.x;
        int y = coord.y;

        if (x == n - 1 && y == n - 1)
            return currentTime;

        for (auto &dir : directions)
        {
            int nx = x + dir[0], ny = y + dir[1];

            if (nx >= 0 && ny >= 0 && nx < n && ny < n)
            {
                int nextTime = max(currentTime, entryTime[nx][ny]);
                if (nextTime < visited[nx][ny])
                {
                    visited[nx][ny] = nextTime;
                    pq.push({nextTime, {nx, ny}});
                }
            }
        }
    }

    return -1;
}
