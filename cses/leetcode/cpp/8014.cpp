class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        int i = 0, j = 0;
        // Iterate through str1 and str2
        while (i < n && j < m) {
            // If the current characters match, move to the next character in str2
            if (str1[i] == str2[j]) {
                j++;
            }
            // Move to the next character in str1
            i++;
        }
        // If we have reached the end of str2, it is a subsequence of str1
        if (j == m) {
            return true;
        }
        // Otherwise, we need to check if we can make str2 a subsequence of str1 by performing the operation at most once
        int k = 0;
        for (int i = 0; i < n; i++) {
            // If the current character in str1 is the same as the next character in str2, we can increment it cyclically
            if (str1[i] == str2[k]) {
                k++;
                // If we have reached the end of str2, it is a subsequence of str1
                if (k == m) {
                    return true;
                }
            }
        }
        // If we have not found a subsequence, return false
        return false;
    }
};