#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    void oceanicDFS(vector<vector<int>> &heights, vector<vector<bool>> &oceanicVisited, int i, int j, int prev_i, int prev_j) {
        int r = heights.size(), c = heights[0].size();
        if (i < 0 || j < 0 || i >= r || j >= c || oceanicVisited[i][j] || (prev_i >= 0 && prev_j >= 0 && heights[i][j] < heights[prev_i][prev_j])) {
            return;
        }
        oceanicVisited[i][j] = true;
        oceanicDFS(heights, oceanicVisited, i + 1, j, i, j); 
        oceanicDFS(heights, oceanicVisited, i - 1, j, i, j); 
        oceanicDFS(heights, oceanicVisited, i, j + 1, i, j); 
        oceanicDFS(heights, oceanicVisited, i, j - 1, i, j); 
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int r = heights.size(), c = heights[0].size();
        vector<vector<bool>> pacificVisited(r, vector<bool>(c, false));
        vector<vector<bool>> atlanticVisited(r, vector<bool>(c, false));

        for (int i = 0; i < r; i++) {
            oceanicDFS(heights, pacificVisited, i, 0, -1, -1);
        }
        for (int j = 0; j < c; j++) {
            oceanicDFS(heights, pacificVisited, 0, j, -1, -1);
        }

        for (int i = 0; i < r; i++) {
            oceanicDFS(heights, atlanticVisited, i, c - 1, -1, -1);
        }
        for (int j = 0; j < c; j++) {
            oceanicDFS(heights, atlanticVisited, r - 1, j, -1, -1);
        }

        vector<vector<int>> result;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (pacificVisited[i][j] && atlanticVisited[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
};
