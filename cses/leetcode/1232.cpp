
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool checkStraightLine(vector<vector<int>> &coordinates)
    {
        int x0 = coordinates[0][0], y0 = coordinates[0][1], x1 = coordinates[1][0], y1 = coordinates[1][1];
        int dx = x1 - x0, dy = y1 - y0;
        for (int i = 2; i < coordinates.size(); i++)
        {
            int x = coordinates[i][0], y = coordinates[i][1];
            if (dx * (y - y1) != dy * (x - x1))
                return false;
        }
        return true;
    }
};
int main()
{
}