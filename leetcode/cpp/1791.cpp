#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int findCenter(vector<vector<int>> &edges)
    {
        // find the common vertices between two edges
        int a = edges[0][0];
        int b = edges[0][1];
        int c = edges[1][0];
        int d = edges[1][1];
        if (a == c || a == d)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
};