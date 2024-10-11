#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int counter = 0;
        int n = s.length();
        for(int i = 0; i < n; i++){
            //finding for the odd length string
            int l = i, r = i;
            while (l >=0 and r < n and s[l]==s[r]) {
                counter++;
                l--;
                r++;
            }
            //finding for the even length string
            l = i, r = i+1;
            while (l >=0 and r < n and s[l]==s[r]) {
                counter++;
                l--;
                r++;
            }
        }
        return counter;
    }
};
