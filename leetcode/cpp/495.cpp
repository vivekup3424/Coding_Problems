
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int findPoisonedDuration(vector<int> &timeSeries, int duration)
    {
        int count = 0;
        int i = 0;
        while (i < timeSeries.size())
        {
            int start = timeSeries[i];
            int max = timeSeries[i++] + duration - 1;
            while (i < timeSeries.size() && max >= timeSeries[i])
            {
                max = timeSeries[i++] + duration - 1;
            }
            count += (max - start + 1);
        }
        return count;
    }
};

int main()
{
    vector<int> timeSeries = {1, 2};
    int duration = 2;
    Solution A = Solution();
    A.findPoisonedDuration(timeSeries, duration);
}