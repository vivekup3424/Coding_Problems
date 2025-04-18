#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minSwaps(string s) {
        stack<int> stk;
        //vector<int> removinIndices;, let me cut corner's
        for(int i = 0; i < s.size(); i++){
            if(stk.empty()){
                if(s[i]=='['){
                    stk.push(i);
                }
                else{
                    continue;
                }
            }
            else{
                if(s[i]=='['){
                    stk.push(i);
                }
                else{
                    stk.pop();
                }
            }
        }    
        return (stk.size()+1)/2;
    }
};