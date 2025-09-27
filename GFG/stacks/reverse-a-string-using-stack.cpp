#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    string reverse(const string &S){
        stack<char> stk;
        for(char c: S){
            stk.push(c);
        }
        string temp;
        while(!stk.empty()){
            temp.push_back(stk.top());  // Use += operator
            stk.pop();
        }
        return temp;  // Don't forget to return the result
    }
};