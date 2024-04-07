#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> stk;
        vector<int> removingIndices;
        string ans;
        for(int i = 0;i < s.size(); i++){
            char c = s[i];
            if(stk.empty()){
                if(s[i]=='('){
                    stk.push(i);
                }
                else if(s[i]==')'){
                    removingIndices.push_back(i);
                }
                else{
                    continue;
                }
            }
            else{
                if(s[i]=='('){
                    stk.push(i);
                }
                else if(s[i]==')'){
                    stk.pop();
                }
                else{
                    continue;
                }
            }
        }
        for(int i : removingIndices){
            s[i] = '#';
        }
        while(stk.empty()==false){
            s[stk.top()] = '#';
            stk.pop();
        }
        for(char c: s){
            if(c!='#'){
                ans.push_back(c);
            }
        }
        return ans;
    }
};
int main()
{
    Solution A;
    string s = "lee(t(c)o)de)";
    string ans =  A.minRemoveToMakeValid(s);
}