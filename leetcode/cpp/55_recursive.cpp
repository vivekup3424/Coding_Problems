#include <bits/stdc++.h>
using namespace std;

class Solution{
    private:
    bool canJumpFromPosition(vector<int> nums, int position){
        if(position == nums.size()-1)return true;
        //if I get stuck can can't jump anywhere I will return false;
        if(nums[position]==0)return false;

        int furthestPosition = min((int)nums.size()-1, position + nums[position]);
    }
};