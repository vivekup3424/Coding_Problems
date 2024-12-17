#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        map<char,int> freq;
        for(auto c :  s){
            freq[c]++;
        }
        string temp = "";
        while(freq.size()>0){
            for(char c = 'z'; c >= 'a'; c--){
                if(freq[c] > 0){
                    for(int i = 0;  i < min(repeatLimit,freq[c]); i++){
                        temp+=c;
                    }
                    freq[c] -= min(repeatLimit,freq[c]);
                }else{
                    freq.erase(c);
                }
            }
        }
        return temp;
    }
};

int main(){
    auto A = Solution();
    string s = "aababab";
    int repeatLimit = 2;
    cout << A.repeatLimitedString(s, repeatLimit) << endl;
    s = "cczazcc";
    repeatLimit = 3;
    cout << A.repeatLimitedString(s, repeatLimit) << endl;
    s = "kjfdjsdgfsu";
    cout << A.repeatLimitedString(s, repeatLimit) << endl;
    return 0;
}
