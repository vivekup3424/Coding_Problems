#include <bits/stdc++.h>
using namespace std;

template <typename T>
void printMatrix(const vector<vector<T>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}; /* code */
class Solution1
{
public:
    void generatePermutations(vector<vector<int>> &permutations,
                              vector<int> &permutation,
                              vector<bool> visited,
                              int count,
                              int n)
    {
        if (count == n)
        {
            permutations.push_back(permutation);
        }
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                visited[i] = true;
                permutation.push_back(i);
                generatePermutations(permutations, permutation,
                                     visited,
                                     count + 1,
                                     n);
                visited[i] = false;
                permutation.pop_back();
            }
        }
    }
    bool isBeautiful(vector<int> v)
    {
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            if ((i != 0 and v[i] % i != 0) and
                (v[i] != 0 and i % v[i] != 0))
            {
                return false;
            }
        }
        return true;
    }
    int countArrangement(int n)
    {
        vector<vector<int>> permutations;
        vector<int> perm;
        vector<bool> visited(n, false);
        generatePermutations(permutations, perm,
                             visited, 0, n);
        printMatrix(permutations);
        // now check if these vectors are beautiful or not
        int count = 0;
        for (auto p : permutations)
        {
            if (isBeautiful(p))
            {
                count++;
            }
        }
        cout << "Count = " << count << endl;
        return count;
    }
    // Time complexity = O(n^n), this would cause TLE
    // I need to make backtracking more efficient by using early termination
};

// not much code will change
class Solution
{
public:
    void generatePermutations(vector<vector<int>> &permutations,
                              vector<int> &permutation,
                              vector<bool> visited,
                              int count,
                              int n)
    {
        if (count == n)
        {
            permutations.push_back(permutation);
        }
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                visited[i] = true;
                permutation.push_back(i);
                generatePermutations(permutations, permutation,
                                     visited,
                                     count + 1,
                                     n);
                visited[i] = false;
                permutation.pop_back();
            }
        }
    }
    bool isBeautiful(vector<int> v)
    {
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            if ((i != 0 and v[i] % i != 0) and
                (v[i] != 0 and i % v[i] != 0))
            {
                return false;
            }
        }
        return true;
    }
    int countArrangement(int n)
    {
        vector<vector<int>> permutations;
        vector<int> perm;
        vector<bool> visited(n, false);
        generatePermutations(permutations, perm,
                             visited, 0, n);
        printMatrix(permutations);
        // now check if these vectors are beautiful or not
        int count = 0;
        for (auto p : permutations)
        {
            if (isBeautiful(p))
            {
                count++;
            }
        }
        cout << "Count = " << count << endl;
        return count;
    }
    // Time complexity = O(n^n), this would cause TLE
    // I need to make backtracking more efficient by using early termination
};

int main()
{
    Solution A;
    A.countArrangement(15);
}