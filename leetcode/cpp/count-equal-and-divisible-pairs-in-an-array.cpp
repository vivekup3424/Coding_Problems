#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        map<int,int>freq;
        for(auto num:nums){
            freq[num]++;
        }
        int sum = 0;
        for(auto it:freq){
            sum+=((it.second)*(it.second+1))/2;
        }
        return sum;
    }
};
