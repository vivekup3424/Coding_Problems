#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    bool isCircularSentence(string sentence) {
        vector<string> words;
        string temp = "";
        for(char c : sentence){
            if(c == ' '){
                if(temp.size()>0){
                    words.push_back(temp);
                    temp.clear(); //clear word next one
                }
            }else{
                temp += c;
            }
        }
        if(temp.size()>0){
            words.push_back(temp);
        }
        int n  = words.size();
        for(int i = 0; i < n; i++){
            int j = (i + 1)%n;
            if(words[i].back() != words[j].front()){
                cout<<words[i].back()<<"=>"<<words[j].front()<<endl;
                return false;
            }
        }
        return true;
    }
};
//Better Approach
class SolutionBetter {
public:
    bool isCircularSentence(string sentence) {
        int n = sentence.size();
        if(sentence[0] != sentence[n-1]) return false;

        for(int i=1; i<n-1; i++){
            if(sentence[i] == ' '){
                if(sentence[i-1] != sentence[i+1]) return false;
            }
        }
        return true;
    }
};
