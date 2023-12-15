
#include <bits/stdc++.h>
using namespace std;
int slope(int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
        return INT_MAX - 1;
    else
        return (y2 - y1) / (x2 - x1);
}
class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int maximum_points = 0;
        for (int i = 0; i < points.size(); i++)
        {
            unordered_map<int, int> mp;
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < points.size(); j++)
            {
                int x2 = points[j][0], y2 = points[j][1];
                int m = slope(x1, y1, x2, y2);
                mp[m]++;
                maximum_points = max(maximum_points, mp[m] + 1);
            }
        }
        return maximum_points;
    }
};

// AI-coded solution
class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n <= 2)
            return n; // If there are 2 or fewer points, return the number of points.

        int maxPoints = 2; // At least 2 points are always on the same line.

        for (int i = 0; i < n; i++)
        {
            unordered_map<double, int> slopeCount; // Use double for slope to handle floating-point slopes.

            int duplicatePoints = 0; // Count of points with the same coordinates as points[i].

            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue; // Skip the same point.

                if (points[i] == points[j])
                {
                    duplicatePoints++;
                }
                else
                {
                    double slope = calculateSlope(points[i], points[j]);
                    slopeCount[slope]++;
                }
            }

            int localMax = duplicatePoints + 1; // At least, there are duplicatePoints + 1 points on the same line.

            for (const auto &[slope, count] : slopeCount)
            {
                localMax = max(localMax, count + 1); // +1 for the original point points[i].
            }

            maxPoints = max(maxPoints, localMax);
        }

        return maxPoints;
    }

private:
    double calculateSlope(const vector<int> &p1, const vector<int> &p2)
    {
        if (p1[0] == p2[0])
            return DBL_MAX; // Vertical line, use a large value.
        return static_cast<double>(p2[1] - p1[1]) / (p2[0] - p1[0]);
    }
};

int main()
{
    ;
}