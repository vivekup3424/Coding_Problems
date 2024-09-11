#include <bits/stdc++.h>
using namespace std;
// 2,3,1,4,3,5
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long count = 0;
        int n = nums.size();
        int start = 0, end = 0;
        while(end < n){
            int sum = nums[end], t = 1;
            while(end < n && sum * t <= k){
                sum += nums[++end];
                t++;
            }
            t--;
            count += (t*(t+1))/2;
            start = end; 
        }
        return count;
    }
};
