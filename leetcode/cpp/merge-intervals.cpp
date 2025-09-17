#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> answer;
        for(auto nextInterval : intervals){
            if(answer.size()==0 || answer.back()[1] < nextInterval[0]){
                answer.push_back(nextInterval);
            }
            else{
                answer.back()[1] = max(answer.back()[1], nextInterval[1]);
            }
        }
        return answer;
    }
};