#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& nums) {
        long long n = nums.size();
        if (n == 1) return nums[0] * nums[0];

        auto computeGCD = [&](long long a, long long b) { return gcd(a, b); };
        auto computeLCM = [&](long long a, long long b) { return (a / computeGCD(a, b)) * b; };

        long long totalGCD = nums[0], totalLCM = nums[0];
        for (long long i = 1; i < n; ++i) {
            totalGCD = computeGCD(totalGCD, nums[i]);
            totalLCM = computeLCM(totalLCM, nums[i]);
        }
        
        long long maxScore = totalGCD * totalLCM;

        for (long long i = 0; i < n; ++i) {
            long long gcdExcludingI = 0;
            long long lcmExcludingI = 1;
            bool first = true;

            for (long long j = 0; j < n; ++j) {
                if (i == j) continue;
                if (first) {
                    gcdExcludingI = nums[j];
                    lcmExcludingI = nums[j];
                    first = false;
                } else {
                    gcdExcludingI = computeGCD(gcdExcludingI, nums[j]);
                    lcmExcludingI = computeLCM(lcmExcludingI, nums[j]);
                }
            }

            long long currentScore = gcdExcludingI * lcmExcludingI;
            maxScore = max(maxScore, currentScore);
        }

        return maxScore;
    }
};
