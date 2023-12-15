
#include <bits/stdc++.h>
using namespace std;
// Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
/**
 * Since total sum is being asked we can use dp
 * now what would be the base-case
 * Base case :- matrix is 1*1, return the value whether that cell is 1 or 0
 *
 * Recursive approach
 * count(matrix, int n) = list of all n*n matrices containing all 1's + count(matrix,n-1)
 * Since 1<=n<=300, base case = count(matrix,1) = 1 if matrix[0][0] == 1 else 0
 *
 */
class Solution int recCountSquares(vector<vector<int>> &matrix, int x1, int x2, int y1, int y3)
{
    int sum = 0;
    if (n == 1)
        return sum += (matrix[0][0] == 1);
    else
        for (int i = 0; i)
}
int main()
{
}