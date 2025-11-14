#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(string s) {
        int i = s.size() - 1, j = s.size() - 1;
        int count = 0;
        while(j>=0){
            if(s[j] == '0'){
                j--;
            }else{
                swap(s[i], s[j]);
                i--;
                j--;
                count+= abs(i - j);
            }
        }
        return count;
    }
};