#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spirallyTraverse(vector<vector<int>> &mat) {
        int topRow = 0, bottomRow = mat.size() - 1;
        int leftCol = 0, rightCol = mat[0].size() - 1;
        vector<int> ans;
        while (topRow <= bottomRow && leftCol <= rightCol) {
            for (int j = leftCol; j <= rightCol; j++) {
                ans.push_back(mat[topRow][j]);
            }
            topRow++;
            for (int i = topRow; i <= bottomRow; i++) {
                ans.push_back(mat[i][rightCol]);
            }
            rightCol--;
            if (topRow <= bottomRow) {
                for (int j = rightCol; j >= leftCol; j--) {
                    ans.push_back(mat[bottomRow][j]);
                }
                bottomRow--;
            }
            if (leftCol <= rightCol) {
                for (int i = bottomRow; i >= topRow; i--) {
                    ans.push_back(mat[i][leftCol]);
                }
                leftCol++;
            }
        }
        return ans;
    }
};
