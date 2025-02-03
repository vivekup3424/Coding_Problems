#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int l = 1, n = nums.size();
        //first find increasing
        int i = 0;
        while(i <n){
            int c = 1;
            while(i+1<n and nums[i]<nums[i+1]){
                c++;
                l = max(l,c);
                i++;
            }
            i++;
        }
        i = 0;
        while(i <n){
            int c = 1;
            while(i+1<n and nums[i]>nums[i+1]){
                c++;
                l = max(l,c);
                i++;
            }
            i++;
        }
        return l;
    }
};
