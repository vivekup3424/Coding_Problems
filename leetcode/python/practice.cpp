#include <bits/stdc++.h>
using namespace std;
int solve(int N, int M, vector<vector<int>> A) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    auto isValid = [&](int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < M;
    };
    int maxProfit = 0;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cellValue = A[i][j];
            for (int d = 0; d < 4; d++) {
                int ni = i + directions[d].first;
                int nj = j + directions[d].second;

                if (isValid(ni, nj)) {
                    int neighborValue = A[ni][nj];
                    if (!visited[ni][nj] && ni + directions[d ^ 1].first == i && nj + directions[d ^ 1].second == j) {
                        maxProfit += pow(abs(cellValue - neighborValue), 2);
                        visited[i][j] = visited[ni][nj] = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                int bestNeighborValue = 0;
                for (int d = 0; d < 4; d++) {
                    int ni = i + directions[d].first;
                    int nj = j + directions[d].second;
                    if (isValid(ni, nj)) {
                        bestNeighborValue = max(bestNeighborValue, A[ni][nj]);
                    }
                }
                maxProfit += bestNeighborValue;
            }
        }
    }
    return maxProfit;
}
int main() {
    int N,M;
    cin>>N>>M;
    vector<vector<int>> A;
    for (int i = 0; i < N; i++)
    {
        vector<int> v;
        for (int j = 0; j < M; j++)
        {
            int temp;
            cin>>temp;
            v.push_back(temp);
        }
        A.push_back(v);
    }
    cout << solve(N, M, A) << endl;
    return 0;
}
