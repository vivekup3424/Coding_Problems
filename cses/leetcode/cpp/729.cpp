#include <bits/stdc++.h>
using namespace std;
class MyCalendar
{
public:
    vector<pair<int, int>> meetings; // end,start
    MyCalendar()
    {
        ;
    }

    bool book(int start, int end)
    {
        for (int i = 0; i < meetings.size(); i++)
        {
            if (start < meetings[i].first and
                start >= meetings[i].second)
            {
                return false;
            }
            else if (start < meetings[i].second and
                     end > meetings[i].second)
            {
                return false;
            }
        }
        meetings.push_back({end, start});
        sort(meetings.begin(), meetings.end());
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */