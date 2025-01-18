#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int minCost(vector<vector<int>>& grid) {
        return recurse(grid, 0, 0, 0);
    }
};:w
