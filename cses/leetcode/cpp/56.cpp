
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    static bool s(vector<int> &a, vector<int> &b)
    {
        if (a[0] != b[0])
            return a[0] < b[0];
        return a[1] < b[1]; // when a[0]==b[0]
    }
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        // sort the intervals
        sort(intervals.begin(), intervals.end(), s);
        vector<vector<int>> results;
        // merge the intervals
        for (auto interval : intervals)
        {
            if (results.empty())
            {
                results.push_back(interval);
            }
            else
            {
                if (results.back()[0] == interval[0] and results.back()[1] == interval[1])
                    continue;
                else if (results.back()[1] < interval[1] and interval[0] <= results.back()[1])
                {
                    results.back()[1] = interval[1];
                }

                else
                {
                    results.push_back(interval);
                }
            }
        }
        return results;
    }
};
// Function to print a 2D vector
void printMatrix(const std::vector<std::vector<int>> &vec)
{
    for (const auto &row : vec)
    {
        for (const auto &num : row)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    // Create a vector of vectors
    std::vector<std::vector<int>> vec = {
        {1, 3},
        {15, 18},
        {8, 10},
        {2, 6}};
    Solution *A = new Solution();
    printMatrix(A->merge(vec));
    // Print the sorted vector
    std::cout << "Sorted vector:" << std::endl;
    printMatrix(vec);

    return 0;
}