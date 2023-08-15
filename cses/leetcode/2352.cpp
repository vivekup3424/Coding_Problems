
#include <bits/stdc++.h>
using namespace std;
class Solution1 // I am getting TLE for this
{
public:
    int equalPairs(vector<vector<int>> &grid)
    {
        unordered_set<string> s;
        // getting rows
        int i = 0;
        int x = grid.size(), y = grid[0].size();
        while (i < x)
        {
            vector<int> row;
            for (auto num : grid[0])
            {
                row.push_back(num);
            }
            string key(row.begin(), row.end());
            s.insert(key);
        }
        int counter = 0;
        int j = 0;
        while (j < y)
        {
            vector<int> col;
            for (int i = 0; i < x; i++)
            {
                col.push_back(grid[i][j]);
            }
            string key(col.begin(), col.end());
            if (s.find(key) != s.end())
            {
                counter++;
            }
        }
        return counter;
    }
};

// Method 2:- Using hash function and set data structure
struct hashVector
{
    size_t operator()(const vector<int> &r) const
    {
        size_t c = 0;
        for (int i = 0; i < r.size(); i++)
        {
            c = c * 10 + r[i];
        }
        return c;
    }
};
class Solution2
{
    // this solution is also wrong as I cannot use set, as there can be repeated identical rows
    //:| :( now what to do???
public:
    int equalPairs(vector<vector<int>> &grid)
    {
        unordered_set<vector<int>, hashVector> s;
        int x = grid.size(), y = grid[0].size();
        int i = 0;
        while (i < x)
        {
            s.insert(grid[i++]);
        }
        int counter = 0;
        int j = 0;
        while (j < y)
        {
            vector<int> v;
            for (int i = 0; i < x; i++)
                v.push_back(grid[i][j]);
            if (s.find(v) != s.end())
                counter++;
            j++;
        }
        return counter;
    }
};

// Method 3
class Solution3
{
    // TLE here as well
public:
    size_t hashVec(vector<int> &r)
    {
        size_t c = 0;
        for (int i = 0; i < r.size(); i++)
        {
            c = c * 10 + r[i];
        }
        return c;
    }
    // idea since I am using hash, hence I can use hashmap to store the number of rows
    // having the same hash and hence make the counting accurate in place using the set data structure
    int equalPairs(vector<vector<int>> &grid)
    {
        unordered_map<size_t, vector<int>> mp;
        int x = grid.size(), y = grid[0].size();
        int i = 0;
        while (i < x)
        {
            mp[hashVec(grid[i])].push_back(i);
        }
        int counter = 0;
        int j = 0;
        while (j < y)
        {
            vector<int> v;
            for (int i = 0; i < x; i++)
                v.push_back(grid[i][j]);
            counter += mp[hashVec(v)].size();
            j++;
        }
        return counter;
    }
};
class Solution
{
public:
    size_t hashVec(vector<int> &r)
    {
        size_t c = 0;
        for (int i = 0; i < r.size(); i++)
        {
            c = c * 10 + r[i];
        }
        return c;
    }
    int equalPairs(vector<vector<int>> &grid)
    {
        unordered_map<size_t, int> rowCounts;
        unordered_map<size_t, int> colCounts;
        int x = grid.size(), y = grid[0].size();
        }
} int main()
{
}