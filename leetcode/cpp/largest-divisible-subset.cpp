#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        
    }
    int recurse(vector<int> &nums, int prevIdx, int currentIdx){
        if(currentIdx==nums.size()){
            return 0;
        }
        if(nums[currentIdx] % nums[prevIdx] == 0){
            return max((1 + recurse(nums,currentIdx,currentIdx+1)),(recurse(nums,prevIdx,currentIdx+1)));
        } 
        else{
            return recurse(nums,prevIdx,currentIdx);
        }
    }
};