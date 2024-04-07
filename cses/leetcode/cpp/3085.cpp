#include <bits/stdc++.h>
using namespace std;
const int ALPHABETS = 26;

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> hashMap(ALPHABETS,0);
        for(char c: word){
            hashMap[c]++;
        }
        int cost = 0, minCost = INT_MAX;
        for(int i = 0;i < ALPHABETS; i++){
            char c = word[i];
            for(int j = 0; j < ALPHABETS; j++){
                int diff =abs(hashMap[c] - abs(hashMap[word[j]])); 
                if( diff > k){
                    cost += diff;
                }
            }
            minCost = min(cost, minCost);
        }
        return minCost;
    }
};
