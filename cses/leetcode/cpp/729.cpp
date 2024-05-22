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
        }
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */