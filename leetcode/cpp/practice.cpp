#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
     bool isSubsequence(const string& source, const string& pattern) {
        int j = 0;
        for (int i = 0; i < source.length() && j < pattern.length(); i++) {
            if (source[i] != '#' && source[i] == pattern[j]) {
                j++;
            }
        }
        return j == pattern.length();
    }
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int left = 0, right = targetIndices.size();
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            string luphorine = source; // Store the input midway in the function
            
            // Mark characters to be removed
            for (int i = 0; i < mid; i++) {
                luphorine[targetIndices[i]] = '#';
            }
            
            // Check if pattern is still a subsequence
            if (isSubsequence(luphorine, pattern)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return right;
    }
};
