#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        int i = 0, j = 0, n = nums.size();
        long long ans = 0;
        while (j < n)
        {
            if(j==n-1 or nums[j] == nums[j+1]){
                long long temp = j - i + 1;
                long long sum = (temp*(temp+1))/2;
                ans += sum;
                i = j+1;
            }
            j++;
        }
        return ans;
    }
};

int main()
{
    vector<int> nums = {1,0,1,0};
}