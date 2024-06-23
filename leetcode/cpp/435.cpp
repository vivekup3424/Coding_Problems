#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        // I can reduce this problem to 6.2 Scheduling
        // portion of CPH book
        vector<pair<int, int>> p; // endTime,startTime
        ll n = intervals.size();
        for (int i = 0; i < n; i++)
        {
            p.push_back({intervals[i][1], intervals[i][0]});
        }
        sort(p.begin(), p.end());
        ll time = p[0].second;
        ll count = 0;
        for (int i = 0; i < n; i++)
        {
            if (p[i].second >= time)
            {
                count++;
                time = p[i].first;
            }
        }
        return intervals.size() - count;
    }
};
int main()
{
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    Solution A;
    ll m = A.eraseOverlapIntervals(intervals);
}