#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    static bool comp(vector<int> a, vector<int> b)
    {
        if (a[1] < b[1])
        {
            return true;
        }
        else
            return a[0] < b[0];
    }
    vector<vector<int>> mergeInterval(vector<vector<int>> &meetings)
    {
        int n = meetings.size();
        sort(meetings.begin(), meetings.end(), comp);
        vector<vector<int>> ans;
        for (int i = 0; i < n;)
        {
            int startTime = meetings[i][0];
            int endTime = meetings[i][1];
            while (i < n && meetings[i][0] <= endTime)
            {
                startTime = min(startTime, meetings[i][0]);
                endTime = max(endTime, meetings[i][1]);
                i++;
            }
            ans.push_back({startTime, endTime});
        }
        return ans;
    }
    int countDays(int days, vector<vector<int>> &meetings)
    {
        vector<vector<int>> ans = mergeInterval(meetings);
        ans = mergeInterval(ans);
        // print the merged intervals
        for (auto v : ans)
        {
            cout << v[0] << " " << v[1] << endl;
        }
        // number of days in meeting
        int sum = 0;
        for (auto v : ans)
        {
            sum += v[1] - v[0] + 1;
        }
        cout << days - sum << endl;
        return days - sum;
    }
};
int main()
{
    vector<vector<int>> meetings = {{5, 7}, {1, 3}, {9, 10}};
    int days = 10;
    Solution().countDays(days, meetings);
}