#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        int total = (n*(n+1))/2;
        int median = (total+1)/2;
        if(median<=n)return 1;
        else{
            median-=n;
            //collecting two childs at a time
            vector<int> num_distincts;
            for(int i = 0; i <n-1;i++){
                if(nums[i]==nums[i+1]){
                    num_distincts.push_back(1);
                }
                else{
                    num_distincts.push_back(2);
                }
            }
            sort(num_distincts.begin(),num_distincts.end());
            return num_distincts[median-1];            
        }
    }
};