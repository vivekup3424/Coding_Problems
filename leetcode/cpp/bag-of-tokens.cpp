#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(),tokens.end());
        int l = 0, r = tokens.size() - 1, s = 0;
        while(l<=r){
            if(power >= tokens[l]){
                power -= tokens[l++];
                s++;
            }else if(s > 0){
                power += tokens[r--];
                s--;
            }
        }
        return s;
    }
};
