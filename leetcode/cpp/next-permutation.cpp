#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    void nextPermutation(vector<int> &nums){
        int pivot_idx = -1;
        for(int i = nums.size()-2; i >= 0; i--){
            if(nums[i] < nums[i+1]){
                pivot_idx=i;
                break;
            }
        }
        int first = pivot_idx+1, last = nums.size()-1;
        while(first<last){
            swap(nums[first++], nums[last--]);
        }
        if(pivot_idx!=-1){
            for(int i = pivot_idx+1;i < nums.size(); i++){
                if(nums[i] > nums[pivot_idx]){
                    swap(nums[i], nums[pivot_idx]);
                    return;
                }
            }
        }
        return;
    }
};