#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxScore(vector<vector<int>> &grid)
    {
        map<int, priority_queue<int>> mp;
        for (auto e : grid)
        {
            priority_queue<int> p;
            for (auto i : e)
            {
                p.push(i);
            }
        }
    }
};