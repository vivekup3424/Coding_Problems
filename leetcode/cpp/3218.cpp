#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minimumCost(int m, int n, vector<int> &horizontalCut, vector<int> &verticalCut)
    {
        // Using greater<int> to make max-heap
        priority_queue<int> maxHorizontal(horizontalCut.begin(), horizontalCut.end());
        priority_queue<int> maxVertical(verticalCut.begin(), verticalCut.end());

        int verticalCount = 1, horizontalCount = 1;
        long long totalCost = 0;

        while (!maxVertical.empty() && !maxHorizontal.empty())
        {
            if (maxVertical.top() > maxHorizontal.top())
            {
                totalCost += maxVertical.top() * horizontalCount;
                verticalCount++;
                maxVertical.pop();
            }
            else
            {
                totalCost += maxHorizontal.top() * verticalCount;
                horizontalCount++;
                maxHorizontal.pop();
            }
        }

        while (!maxVertical.empty())
        {
            totalCost += maxVertical.top() * horizontalCount;
            verticalCount++;
            maxVertical.pop();
        }

        while (!maxHorizontal.empty())
        {
            totalCost += maxHorizontal.top() * verticalCount;
            horizontalCount++;
            maxHorizontal.pop();
        }

        return totalCost;
    }
};
