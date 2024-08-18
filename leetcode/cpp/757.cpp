#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int intersectionSizeTwo(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b)
             {
            if(a[1]==b[1]){
                return a[0] > b[0];
            }
            return a[1] < b[1]; });
        int len = 0, largest = -1, secondLargest = -1;
        for (auto interval : intervals)
        {
            int a = interval[0];
            int b = interval[1];
        }
    }
};