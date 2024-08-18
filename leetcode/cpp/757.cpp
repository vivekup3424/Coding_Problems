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
    }
};