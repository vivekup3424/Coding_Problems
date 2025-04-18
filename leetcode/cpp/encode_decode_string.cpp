#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string encode(vector<string>& strs) {
        string ans;
        for(const string &str: strs){
            ans += str + "#"+to_string(str.length());
        }
        return ans;
    }

    vector<string> decode(string s) {
        vector<string> ans;
        int i = 0;
        int n = s.size();
        for(; i < n; ){
            string temp = "";
        }
    }
};
