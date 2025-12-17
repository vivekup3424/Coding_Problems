#include <bits/stdc++.h>
using namespace std;

class Solution{
    private:
    string sanitizeString(string s){
        string temp;
        for(char c : s){
            if(('a' <= c && c <= 'z') || ('0'<=c && c <= '9')){
                temp.push_back(c);
            }else if('A' <= c && c <= 'Z'){
                c = c - 'A' + 'a';
                temp.push_back(c);
            }else{
                continue;
            }
        }
        cout<<"temp = "<<temp<<endl;
        return temp;
    }
    public:
    bool isPalindrome(string s){
        string t = sanitizeString(s);
        int l = 0, r = (int)t.size()-1;
        while(l<r){
            if(t[l]!=t[r]){
                return false;
            }
        }
        return true;
    }
};