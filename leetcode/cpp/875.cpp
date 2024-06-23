#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int calculateTime(vector<int> &piles, int speed)
    {
        int total = 0;
        for (int i = 0; i < piles.size(); i++)
        {
            total += piles[i] / speed;
            if (piles[i] % speed > 0)
            {
                total++;
            }
        }
        return total;
    }
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int l = 1, r = *max_element(piles.begin(), piles.end());
        sort(piles.begin(), piles.end());
        int ans = r;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            int time = calculateTime(piles, mid);
            if (time <= h)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return ans;
    }
};