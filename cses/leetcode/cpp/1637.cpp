
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxWidthOfVerticalArea(vector<vector<int>> &points)
    {
        set<int> abcissa; // x-coordinates of the vector
        for (int i = 0; i < points.size(); i++)
        {
            abcissa.insert(points[i][0]);
        }
        int maxDiff = 0;
        // iterate over the set abcissa , and find the maximum difference
        int prev = *abcissa.begin(); // first element in the set
        for (int x : abcissa)
        {
            maxDiff = max(maxDiff, x - prev);
            prev = x;
        }
        return maxDiff;
    }
};
int main()
{
}