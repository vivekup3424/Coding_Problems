#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    long long countSubarrays(vector<int> &nums, long long k){
        long long count = 0;
        for(int i = 0; i < nums.size(); i++){
            long long sum = 0, l = 0;
            for(int j = i; j < nums.size(); j++){
                sum+=nums[j];
                l++;
                if(sum*l<k){
                    count+=1;
                }
            }
        }
        return count;
    }
};
