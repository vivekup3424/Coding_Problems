#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int counter = 0;
        int width = 0;
        int start = 0;
        while(start < words.size()){
            width += words[start++].size();
            counter++;
            int nextWidth = width + words[start].size();
            if(nextWidth >)
        }
    }
};
