#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w", stdout);
    int N;
    cin >> N;
    vector<bool> original(N, false);
    vector<vector<int>> moves;
    for (int i = 0; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        moves.push_back({a, b, c});
    }
    int maxScore = 0;
    for (int i = 0; i < N; i++)
    {
        vector<bool> position = original;
        position[i] = true;
        int currentScore = 0;
        for (auto move : moves)
        {
            swap(position[move[0] - 1], position[move[1] - 1]);
            if (position[move[2] - 1] == true)
            {
                currentScore++;
            }
        }
        maxScore = max(maxScore, currentScore);
    }
    cout << maxScore << endl;
    return 0;
}
