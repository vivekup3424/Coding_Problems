#include <bits/stdc++.h>
using namespace std;

bool hasGeekSubsequence(string str){
    string target = "geek";
    auto idx = 0;
    for(char c : str){
        if(c==str[idx]){
            idx++;
        }
    }
    return idx==target.size();
}
