#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        const int MOD = 1e9 + 7;
        vector<long long> freq(26, 0);
        for(char c : s) {
            freq[c - 'a']++;
        }
        while(t > 0) {
            vector<long long> temp(26, 0);
            if(t >= 30) {  // Process 30 steps at a time to avoid overflow
                long long multiplier = 1LL << 30;  // Safe value for bit shifting
                for(int i = 0; i < 26; i++) {
                    if(freq[i] > 0) {
                        if(i == 25) {  // 'z'
                            // Each 'z' becomes 2^30 'a's and 'b's
                            temp[0] = (temp[0] + (freq[i] * multiplier) % MOD) % MOD;
                            temp[1] = (temp[1] + (freq[i] * multiplier) % MOD) % MOD;
                        } else {
                            // Non-'z' characters just move forward 30 positions
                            int newPos = (i + 30) % 26;
                            temp[newPos] = (temp[newPos] + freq[i]) % MOD;
                        }
                    }
                }
                t -= 30;
            } else {
                // Process one step at a time for remaining transformations
                for(int i = 0; i < 26; i++) {
                    if(freq[i] > 0) {
                        if(i == 25) {  // 'z'
                            temp[0] = (temp[0] + freq[i]) % MOD;  // 'a'
                            temp[1] = (temp[1] + freq[i]) % MOD;  // 'b'
                        } else {
                            temp[i + 1] = (temp[i + 1] + freq[i]) % MOD;
                        }
                    }
                }
                t--;
            }
            freq = temp;
        }
        
        // Calculate final length
        int result = 0;
        for(long long count : freq) {
            result = (result + count) % MOD;
        }
        return result;
    }
};
