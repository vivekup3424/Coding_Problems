#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int naiveMethod(vector<int> & nums){
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            for(int j = 0; j < i; j++){
                if(nums[j]>2LL * nums[i]){
                    count+=1;
                }
            }
        }
        return count;
    }
};
