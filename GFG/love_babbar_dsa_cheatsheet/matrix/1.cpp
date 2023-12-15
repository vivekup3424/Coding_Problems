// Print a matrix in spiral form
#include <bits/stdc++.h>
using namespace std;
void printVector(vector<int> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << "\n";
}
// Method 1
/*
vector<int> spiralOrder(vector<vector<int>> &matrix, int rows, int cols) /// rows - num of rows, cols = num of columns
{
    vector<int> ans;
    bool seen[rows][cols]; // detemines wether the place is visited or not
    memset(seen, false, rows * cols);

}
*/

// Method 2
// Print the given matrix in spiral form by dividing the matrix into cycles
vector<int> spiralPrint(vector<vector<int>> &matrix, int rows, int cols)
{
    int k = 0, l = rows - 1, m = 0, n = cols - 1;
    /* k - starting row index
        l - ending row index
        m - starting column index
        n - ending column index
        i - iterator

        k
       _____
    m |     |  n
      |_____|
        l
    */
    vector<int> ans;
    while (k <= l and m <= n)
    {
        // print the first row
        for (int i = m; i <= n; i++)
        {
            ans.push_back(matrix[k][i]);
        }
        k++;

        // print the last column
        for (int i = k; i <= l; i++)
        {
            ans.push_back(matrix[i][n]);
        }
        n--;

        // print the last row
        for (int i = n; i >= m; i--)
        {
            ans.push_back(matrix[l][i]);
        }
        l--;

        // print the first column
        for (int i = l; i >= k; i--)
        {
            ans.push_back(matrix[i][m]);
        }
        m++;
    }
    // Time complexity = 0(mn)
    printVector(ans);
    return ans;
}

// Method 3
// Print a matrix in a spiral using recursion

// Method 4
// Print a given matrix in spiral using DFS
int main()
{
    int rows = 4, cols = 4;
    vector<vector<int>> v = {{1, 2, 3, 4},
                             {5, 6, 7, 8},
                             {9, 10, 11, 12},
                             {13, 14, 15, 16}};
    spiralPrint(v, rows, cols);
    return 0;
}