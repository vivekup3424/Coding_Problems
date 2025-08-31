#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/**
 *0: Empty ward
 1: Cells have uninfected patients
 2: Cells have infected patients
*/
int helpaterp(vector<vector<int>> hospital)
{
    int N = hospital.size();
    queue<pair<pair<int, int>, int>> q;
    int time = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (hospital[i][j] = 2)
            {
                q.push({{i, j}, time});
            }
        }
    }
    vector<int> dir_X = {1, 0, -1, 0};
    vector<int> dir_Y = {0, 1, 0, -1};
    int max_time = time;
    while (q.size() > 0)
    {
        auto node = q.front().first;
        int t = q.front().second;
        max_time = max(max_time, t);
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int child_X = node.first + dir_X[i];
            int child_Y = node.first + dir_Y[i];
            if (child_X < 0 or child_Y < 0 or hospital[child_X][child_Y] != 1 or child_X > N or child_Y > N)
            {
                continue;
            }
            else
            {
                q.push({{child_X, child_Y}, t + 1});
            }
        }
    }
    return max_time;
}