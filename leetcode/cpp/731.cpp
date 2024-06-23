#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class MyCalendarTwo
{
public:
    vector<pair<ll, ll>> meetings;
    MyCalendarTwo()
    {
        // whatever, I dont know what to do here??
    }

    bool book(int start, int end)
    {
        int counter = 0;
        for (auto m : meetings)
        {
            if (end >= m.second and end < m.first)
            {
                counter++;
            }
            else if (start >= m.second)
        }
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */