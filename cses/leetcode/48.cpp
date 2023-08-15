
#include <bits/stdc++.h>
using namespace std;

int main()
{
}
class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        vector<vector<int>> temp = matrix;
        int x = matrix.size(), y = matrix[0].size();
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
                matrix[j][x - i - 1] = temp[i][j];
        }
        return;
    }
};