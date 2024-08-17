#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long maxPoints(vector<vector<int>> &points)
    {
        /*
            (columns)
            <-- n -->
            _________
          ^ |        |
          m |        | (rows)
            |        |
            ----------
        */

        int m = points.size();
        int n = points[0].size();
        int curr_col = -1, curr_element = -1;
        long long totalScore = 0;
        // getting the first element
        for (auto j = 0; j < n; j++)
        {
            if (abs(points[0][j]) > curr_element)
            {
                curr_element = abs(points[0][j]);
                curr_col = j;
            }
        }
        totalScore = curr_element;
        int prev_col = curr_col;
        int prev_element = curr_element;
        for (int i = 1; i < m; i++)
        {
            curr_col = -1;
            curr_element = -1; // maximum value seen till now
            for (int j = 0; j < n; j++)
            {
                // value = current_value - distance
                int value = points[i][j] - abs(j - prev_col);
                if (abs(value) > curr_element)
                {
                    curr_element = abs(value);
                    curr_col = j;
                }
            }
            totalScore += curr_element;
            prev_col = curr_col;
            prev_element = curr_element;
        }
        return totalScore;
    }
};
