#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s){
        stack<char> stk;
        for(char c:s){
            if(stk.empty()){
                if(c=='(')stk.push(c);
                else if(c==')')return false;
                else continue;
            }
            else
            {
                if(c=='(')stk.push(c);
                else if(c==')')stk.pop();
                else continue;
            }
        }
        return stk.empty();
        //linear time complexity
    }
    vector<string> removeInvalidParentheses(string s) {
        queue<pair<string,int>> q; //str and level
        q.push({s,0});
        int minLevel = INT_MAX;
        set<string> ans;
        while(q.empty()==false){
            string current_str = q.front().first;
            int current_lvl = q.front().second;
            if(isValid(current_str) and current_lvl<=minLevel){
                minLevel = current_lvl;
                ans.insert(current_str);
                q.pop();
                continue;
            }
            q.pop();
            for(int i = 0; i < current_str.size(); i++){
                if(current_str[i] == '(' || current_str[i] == ')'){
                    string temp;
                    for(int j = 0; j < current_str.size(); j++){
                        if(j!=i){
                            temp.push_back(current_str[j]);
                        }
                    }
                    q.push({temp,current_lvl+1});
                }
            }
        }
        vector<string> result;
        for(auto i: ans){
            result.push_back(i);
        }
        return result;
    }
};
