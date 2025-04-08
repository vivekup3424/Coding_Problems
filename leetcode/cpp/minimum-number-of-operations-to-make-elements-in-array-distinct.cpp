/**
 * Problem: Make Array Elements Distinct
 * 
 * Given an integer array nums, ensure all elements are distinct using this operation:
 * - Remove 3 elements from the beginning (or all elements if fewer than 3 remain)
 * 
 * Return the minimum operations needed. Note: An empty array is considered valid.
 * 
 * Examples:
 * Ex1: nums = [1,2,3,4,2,3,3,5,7] → Output: 2
 *      After 1st op: [4,2,3,3,5,7]
 *      After 2nd op: [3,5,7] (distinct)
 * 
 * Ex2: nums = [4,5,6,4,4] → Output: 2
 *      After 1st op: [4,4]
 *      After 2nd op: [] (empty)
 * 
 * Ex3: nums = [6,7,8,9] → Output: 0
 *      Already distinct
 * 
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 1 <= nums[i] <= 100
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        map<int,int>freq;
        for(int num : nums){
            freq[num]++;
        }
        int i = 0, n = nums.size(), count = 0;
        while(i<n and freq.size()<(n-i)){
            count++;
            for(int j = 0; j < 3; j++){
                if(i<n){
                    freq[nums[i]]--;
                    if(freq[nums[i]]==0){
                        freq.erase(nums[i]);
                    }
                }
                i++;
            }
        }
        return count;
    }
};
int main(){
    vector<int> v = {1,2,3,4,2,3,3,5,7};
    auto ans = Solution().minimumOperations(v);
    for(auto num : v){
        cout<<num<<" ";
    }
    cout<<endl;
    cout<<ans<<endl;
}
