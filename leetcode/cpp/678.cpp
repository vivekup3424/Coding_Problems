#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<int> star_count(n,0);
        vector<int> opening(n,0);
        for(int i = 0; i < n; i++){
            if(i==0){
                if(s[i]=='*'){
                    star_count[i] = 1;
                }
                else if(s[i]=='('){
                    opening[i] = 1;
                }
                else{
                    opening[i] = -1;
                }
            }
            else{
                if(s[i]=='*'){
                    star_count[i] = 1+star_count[i-1];
                    opening[i] = opening[i-1];
                }
                if(s[i]=='('){
                    opening[i] = 1+opening[i-1];
                    star_count[i] = star_count[i-1];
                }
                else if(s[i]==')'){
                    opening[i] = -1+opening[i-1];
                    star_count[i] = star_count[i-1];
                }
            }
        }
        //bool result = true;
        for(int i = 0; i < n; i++){
            if((opening[i]+star_count[i])<0){
                return false;
            }
        }
        return true;
    }
};
int main(){
    Solution A;
    string s = "(*))";
    bool result = A.checkValidString(s);
}