#include <bits/stdc++.h>
using namespace std;
//trying the memoized way of solving this
enum states{
    GOOD, BAD, UNKNOWN
};
class Solution {
public:
    bool canJumpFromPosition(vector<int> &nums,vector<states> &memo, int n, int position){
        if(memo[position]!=states::UNKNOWN)
            return memo[position] == states::GOOD ? true : false;
        int furthestJump = min(n-1, position + nums[position]);
        for(int nextPosition = position+1; nextPosition <= furthestJump;nextPosition++){
            if(canJumpFromPosition(nums,memo,n,nextPosition)==true){
                memo[position] =  states::GOOD;
                return true;
            }
        }
        memo[position] = states::BAD;
        return false;
    }
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<states> memo(n, states::UNKNOWN);
        return canJumpFromPosition(nums,memo,n,0);
    }
};
int main(){
    
}