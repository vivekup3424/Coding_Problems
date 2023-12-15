// Search in a row wise and column wise sorted matrix

// Given an n x n matrix and an integer x,
// find the position of x in the matrix if it is present.
// Otherwise, print “Element not found”.
// Every row and column of the matrix is sorted in increasing order.
// The designed algorithm should have linear time complexity

/*
01 02 03 04
05 06 07 08
09 10 11 12
13 14 15 16
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX 100
// Method 1
// Traversal
// Time complexity = O(n^2)

// Method 2
// Start the search from the top-right corner of the matrix
// 1. The given number > current number=> the current-row get eliminated
// 2. given number < current number=> current column get eliminated
// 3. given number === current => our search has ended
// TIme complexity = O(n)

// x = given number, n = dimension of matrix
int secondMethod(int matrix[][4], int n, int x)
{
    if (n == 0)
        return -1;
    int smallest = matrix[0][0], largest = matrix[n - 1][n - 1];
    if (x < smallest || x > largest)
        return -1;

    // indices of right-top element
    int i = 0, j = n - 1;
    while (i < n && j >= 0)
    {
        if (matrix[i][j] == x)
        {
            cout << "Element found at " << i << ", " << j;
            return 1;
        }
        if (matrix[i][j] > x)
            j--;

        // Check if mat[i][j] < x
        else
            i++;
    }

    cout << "n Element not found";
    return 0;
}