#include <bits/stdc++.h>
using namespace std;
class SummaryRanges
{
public:
    set<pair<int, int>> st;
    SummaryRanges()
    {
        ;
    }

    void addNum(int value)
    {
        int l = value - 1, r = value + 1;
        if (l < 0)
        {
            l = 0;
        }
        for (auto it : st)
        {
            if (it.first == l or it.second)
        }
    }

    vector<vector<int>> getIntervals()
    {
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */