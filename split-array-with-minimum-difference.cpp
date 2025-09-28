#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    long long splitArray(vector<int> &nums){
        int n = nums.size();
        vector<bool> isIncreasing(n, false), isDecreasing(n,false);
        for(int i = 0; i < n; i++){
            if(i==0){
                isIncreasing[i]=true;
            }
            else if(nums[i]>nums[i-1] && isIncreasing[i-1]==true){
                isIncreasing[i]=true;
            }
        }
        for(int i = n-1; i >= 0; i--){
            if(i==n-1){
                isDecreasing[i]=true;
            }
            else if(nums[i]>nums[i+1] && isDecreasing[i+1]==true){
                isDecreasing[i]=true;
            }
        }
        long long total_sum = accumulate(nums.begin(),nums.end(),0LL);
        long long minDiff = LONG_MAX;
        long long currentSum = 0;
        for(int i = 0; i < n; i++){
            if(isIncreasing[i]==true){
                currentSum+=nums[i];
                if(i+1<n && isDecreasing[i+1]==true){
                    long long currentDiff = abs(total_sum - 2 * currentSum);
                    minDiff = min(minDiff,currentDiff);
                }
            }else{
                break;
            }
        }
        return minDiff != LONG_MAX ? minDiff : -1;
    }
};