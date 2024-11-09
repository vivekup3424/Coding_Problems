#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAddToMakeValid(string s) {
        int opening = 0; //counts the number of opening brackets currently
        int closing = 0; //count the number of extra closing bracket, without the opening bracket paired with them
        for(char c: s){
            if(opening == 0){
                if(c==')'){
                    closing++;
                }
                else{
                    opening++;
                }
            }
            else{
                if(c=='(')opening++;
                else if(c==')')opening--;
            }
        }
        return opening+closing;
    }
};
