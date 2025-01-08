#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    long long calculateScore(string s){
        long long score = 0;
        int n = s.length();
        map<char,queue<int>> indices;
        for(int i = 0; i < n; i++){
            char complement = 25 - s[i];
            indices[s[i]].push(i);
        }
    }
}
