#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        map<int,int>freq;
        for(auto num : nums){
            freq[num]++;
        }
        int numberOfDistinctElements = freq.size();
        int count = 0, n = nums.size();
        for(int i = 0; i < n; i++){
            map<int,int> subarray_freq;
            for(int j = i; j < n; j++){
                subarray_freq[nums[i]]++;
                if(subarray_freq.size()==numberOfDistinctElements){
                    count++;
                }
            }
        }
        return count;
    }
};
int main(){
    vector<int> arr = {1,3,1,2,3};
    cout<<Solution().countCompleteSubarrays(arr)<<endl;
}
