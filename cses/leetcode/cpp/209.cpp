#include <bits/stdc++.h>
using namespace std;
//Method 1 Using brute force calculate the sum of all possible subarrays
//from everypossible index.
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;
        for(int i = 0;i<n;i++)
        {
            // find the sum of all subarray for an index i
            for(int j = i;j<n;j++)
            {
                sum =0;
                for(int k = i;k<j;k++)
                {
                    sum+=nums[k];
                }
                if(sum>=s){
                    ans = min(ans,(j-i+1));
                    break; 
                    // found the smallest 
		    //subarray with sum>=s starting with index i,
		    // hence move to the next index
                }
            }
        }
    }
	//Time Complexity = O(n*n*n) = O(n^3)
	//Space Complexity = O(1)
};

//Method 2 Using Sliding Window Approach

