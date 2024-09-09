#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isPossible(vector<int> &start, int d, int m)
    {
        int n = start.size();
        int prev = start[0];
        for (int i = 1; i < n; i++)
        {
            int element = prev + m;
            if (element <= start[i] + d)
            {
                prev = max(element, start[i]);
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    int maxPossibleScore(vector<int> &start, int d)
    {
        sort(start.begin(), start.end());
        int l = 0, r = INT_MAX, ans = -1, m = -1;
        while (l <= r)
        {
            m = l + (r - l) / 2;
            if (isPossible(start, d, m))
            {
                ans = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return ans;
    }
};