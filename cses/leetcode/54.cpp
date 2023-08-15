// Given an m x n matrix, return all elements of the matrix in spiral order.

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        vector<int> res;
        while (top <= bottom and left <= right)
        {
            // traverse the top row
            for (int i = left; i <= right; i++)
            {
                res.push_back(matrix[top][i]);
            }
            top++;
            // traverse the right column
            for (int i = top; i <= bottom; i++)
            {
                res.push_back(matrix[i][right]);
            }
            right--;
            if (top < bottom and left <= right)
            {
                // traverse the bottom row
                for (int i = right; i >= left; i--)
                {
                    res.push_back(matrix[bottom][i]);
                    bottom--;
                }
                // traverse the left column
                for (int i = bottom; i >= top; i--)
                {
                    res.push_back(matrix[i][left]);
                    left++;
                }
            }
        }
        return res;
    }
};
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        vector<int> res;
        while (res.size() < m * n)
        {
            // traverse the top row
            for (int i = left; i <= right; i++)
            {
                res.push_back(matrix[top][i]);
                top++;
            }
            // traverse the right column
            {
                for (int i = top; i <= bottom; i++)
                {
                    res.push_back(matrix[i][right]);
                    right--;
                }
            }
            //
        }
    }
} void printVector(vector<int> nums)
{
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;
};
int main()
{
}