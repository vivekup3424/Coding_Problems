#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    int removeDuplicates(vector<int> &nums){
        if(nums.size()<2){
            return nums.size();
        }
        int i = 1,j = 1;
        while(i<nums.size()){
            if(nums[j-1]!=nums[i]){
                swap(nums[j],nums[i]);
                j++;
            }
            i++;
        }
        return j;
    }
};