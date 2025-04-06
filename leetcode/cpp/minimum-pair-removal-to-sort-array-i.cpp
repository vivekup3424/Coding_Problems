#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIncreasing(vector<int> &nums){
        int max_element = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(max_element>nums[i]){
                return false;
            }
            max_element = max(max_element,nums[i]);
        }
        return true;
    }
    int minimumPairRemoval(vector<int>& nums) {
        int minSum = INT_MAX, minIdx = -1;
        for(int i = 0; i < nums.size()-1; i++){
            int currentSum = nums[i] + nums[i+1];
            if(currentSum<minSum);
            minSum = currentSum;
            minIdx = i;
        }
        vector<int> temp;
        for(int i = 0 ; i)
    }
};