#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxLength = 0;
        for (int i = 0; i < n; i++) {
            int product = 1;
            int subGCD = nums[i];
            int subLCM = nums[i];
            for (int j = i; j < n; j++) {
                product *= nums[j];
                subGCD = __gcd(subGCD, nums[j]);
                subLCM = (subLCM / __gcd(subLCM, nums[j])) * nums[j];
                if (product == subGCD * subLCM) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        return maxLength;
    }
};
