// solve it thru dp
// this is going to have exponential time complexity

// this code is special to me
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> result;
        for (int i = 0; i < numRows; i++)
        {
            vector<int> r;
            if (i == 0)
            {
                r = {1};
                result.push_back(r);
                continue;
            }
            r.push_back(1);
            for (int j = 0; j < i - 1; j++)
            {
                r.push_back(result[i - 1][j] + result[i - 1][j + 1]);
            }
            r.push_back(1);
            result.push_back(r);
        }
        return result;
    }
    // Time Complexity = O(n^2)
};
// This is crazy, I coded the most optimal code by myself.
int main()
{
    int numRows = 5;
    Solution solution;
    vector<vector<int>> result = solution.generate(numRows);

    // Print the result
    for (const auto &row : result)
    {
        for (const auto &num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}