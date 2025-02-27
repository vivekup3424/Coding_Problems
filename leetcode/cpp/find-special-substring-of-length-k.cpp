#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    bool hasSpecialSubstring(string s, int k){
        int i = 1;
        int n = s.size();
        while(i < n)
        {
            int currentLength = 0;
            int j = i;
            while(j < n and s[i] == s[j]){
                currentLength+=1;
                j++;
            }
            i = j + 1;
            if(currentLength ==  k){
                return true;
            }
        }
        return false; 
    }
};