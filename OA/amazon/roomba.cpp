#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main()
{
    // Given x and y coordinates
    std::vector<int> x = {1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
    std::vector<int> y = {1, 2, 3, 1, 2, 3, 5, 1, 2, 3};

    // Determine the size of the matrix
    int max_x = *max_element(x.begin(), x.end());
    int max_y = *max_element(y.begin(), y.end());

    // Create a matrix filled with 0s
    std::vector<std::vector<int>> original_matrix(max_x, std::vector<int>(max_y, 0));
    // stores the max element encountered from the left for each row
    std::vector<std::vector<int>> left_matrix(max_x, std::vector<int>(max_y, 0));
    // stores the max element encountered from the right for each row
    std::vector<std::vector<int>> right_matrix(max_x, std::vector<int>(max_y, 0));
    // stores the max element encountered from up for each column
    std::vector<std::vector<int>> up_matrix(max_x, std::vector<int>(max_y, 0));
    // stores the max element encoutered from down for each column
    std::vector<std::vector<int>> down_matrix(max_x, std::vector<int>(max_y, 0));

    // Mark the given coordinates in the matrix
    for (size_t i = 0; i < x.size(); ++i)
    {
        original_matrix[x[i] - 1][y[i] - 1] = 1;
    }

    // Output the matrix
    for (const auto &row : original_matrix)
    {
        for (int value : row)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < max_x; i++)
    {
        for (int j = 0; j < max_y; j++)
        {
            if (i == 0)
            {
                up_matrix[i][j] = 0;
            }
            else if (j == 0)
            {
                left_matrix[i][j] = 0;
            }
            else
            {
                left_matrix[i][j] = max(original_matrix[i][j - 1], left_matrix[i][j - 1]);
                up_matrix[i][j] = max(original_matrix[i - 1][j], up_matrix[i - 1][j]);
            }
        }
    }
    for (int i = max_x - 1; i >= 0; i--)
    {
        for (int j = max_y - 1; j >= 0; j--)
        {
            if (i == max_x - 1)
            {
                down_matrix[i][j] = 0;
            }
            else if (j == max_y - 1)
            {
                right_matrix[i][j] = 0;
            }
            else
            {
                right_matrix[i][j] = max(original_matrix[i][j + 1], right_matrix[i][j + 1]);
                down_matrix[i][j] = max(original_matrix[i + 1][j], down_matrix[i + 1][j]);
            }
        }
    }
    int count = 0;
    for (int i = 0; i < max_x; i++)
    {
        for (int j = 0; j < max_y; j++)
        {
            if (left_matrix[i][j] == 1 &&
                right_matrix[i][j] == 1 &&
                up_matrix[i][j] == 1 &&
                down_matrix[i][j] == 1)
            {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}
