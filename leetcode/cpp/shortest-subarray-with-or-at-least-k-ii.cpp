#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        vector<int> activeBitsK(31, 0); // We assume 32-bit integers
        // Calculate the active bits of k
        for (int i = 0; i < 31; i++) {
            if (k & (1 << i)) {
                activeBitsK[i] = 1;
            }
        }
        int start = 0, end = 0;
        int n = nums.size();
        vector<int> windowBits(31, 0);
        int minLength = INT_MAX;
        int currentNumber = 0;
        // Start sliding window
        while (end < n) {
            // Update windowBits for nums[end]
            for (int i = 0; i < 31; i++) {
                if (nums[end] & (1 << i)) {
                    windowBits[i]++;
                    if(windowBits[i]==1){
                        //new bit has been activated
                        currentNumber += (1<<i);
                    }
                }
            }
            // Try to contract the window from the start if it meets the condition
            while (currentNumber >= k && start <= end) {
                minLength = min(minLength, end - start + 1);
                // Remove nums[start] from windowBits
                for (int i = 0; i < 31; i++) {
                    if (nums[start] & (1 << i)) {
                        windowBits[i]--;
                        if (windowBits[i]==0) {
                            currentNumber /= (1<<i);
                        }
                    }
                }
                start++;
            }
            // Move the end of the window forward
            end++;
        }
        return (minLength == INT_MAX) ? -1 : minLength;
    }
};

class Solution2 {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int minLength = INT_MAX;
        int windowStart = 0;
        int windowEnd = 0;
        vector<int> bitCounts(32,0);  // Tracks count of set bits at each position

        // Expand window until end of array
        while (windowEnd < nums.size()) {
            // Add current number to window
            updateBitCounts(bitCounts, nums[windowEnd], 1);

            // Contract window while OR value is valid
            while (windowStart <= windowEnd &&
                   convertBitCountsToNumber(bitCounts) >= k) {
                // Update minimum length found so far
                minLength = min(minLength, windowEnd - windowStart + 1);

                // Remove leftmost number and shrink window
                updateBitCounts(bitCounts, nums[windowStart], -1);
                windowStart++;
            }

            windowEnd++;
        }

        return minLength == INT_MAX ? -1 : minLength;
    }

private:
    // Updates bit count array when adding/removing a number from window
    void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            // Check if bit is set at current position
            if ((number >> bitPosition) & 1) {
                bitCounts[bitPosition] += delta;
            }
        }
    }

    // Converts bit count array back to number using OR operation
    int convertBitCountsToNumber(const vector<int>& bitCounts) {
        int result = 0;
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if (bitCounts[bitPosition] != 0) {
                result |= 1 << bitPosition;
            }
        }
        return result;
    }
};


