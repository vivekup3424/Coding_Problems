#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        if(t.length() > s.length()) {
            return "";
        }
        
        unordered_map<char, int> mt;
        for(char c : t) {
            mt[c]++;
        }
        
        int start = 0, n = s.size();
        int miniLength = INT_MAX, counter = 0;
        int minStart = -1;
        unordered_map<char, int> ms;
        
        for(int end = 0; end < n; end++) {
            char c = s[end];
            
            if(mt.count(c)) {
                ms[c]++;
                if(ms[c] == mt[c]) {
                    counter++;
                }
            }
            
            while(counter == mt.size()) {
                if(end - start + 1 < miniLength) {
                    miniLength = end - start + 1;
                    minStart = start;
                }
                
                if(mt.count(s[start])) {
                    ms[s[start]]--;
                    if(ms[s[start]] < mt[s[start]]) {
                        counter--;
                    }
                }
                start++;
            }
        }
        
        return (miniLength == INT_MAX) ? "" : s.substr(minStart, miniLength);
    }
};

int main (int argc, char *argv[]) {
    
    return 0;
}
