#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        
        // Boyer-Moore Majority Vote Algorithm for 2 candidates
        int candidate1 = 0, candidate2 = 0;
        int count1 = 0, count2 = 0;
        
        // First pass: Find potential candidates
        for (int num : nums) {
            if (count1 == 0 && num != candidate2) {
                candidate1 = num;
                count1 = 1;
            } else if (count2 == 0 && num != candidate1) {
                candidate2 = num;
                count2 = 1;
            } else if (num == candidate1) {
                count1++;
            } else if (num == candidate2) {
                count2++;
            } else {
                count1--;
                count2--;
            }
        }
        
        // Second pass: Verify candidates
        count1 = count2 = 0;
        for (int num : nums) {
            if (num == candidate1) count1++;
            else if (num == candidate2) count2++;
        }
        
        vector<int> result;
        if (count1 > n / 3) result.push_back(candidate1);
        if (count2 > n / 3) result.push_back(candidate2);
        
        return result;
    }
};