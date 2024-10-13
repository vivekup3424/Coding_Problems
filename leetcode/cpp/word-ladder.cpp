#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int editDistance(string word1, string word2){
        int count = 0;
        for(int i = 0; i < min(word1.length(),word2.length()); i++){
            if(word1[i] != word2[i]){
                count++;
            }
        }
        return count;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(),wordList.end()); //Hashset
        //printing all the available words
        for(auto it: wordSet){
            cout<<it<<"=>";
        }
        cout<<endl;

        //getting smallest possible transformation using word ladder
        if(wordSet.find(endWord)==wordSet.end() 
            || beginWord.length() != endWord.length()){
            return 0;
        }
        queue<pair<int,string>> q;
        q.push({1,beginWord});
        while(!q.empty()){
            auto [l,w] = q.front();
            q.pop();
            wordSet.erase(w);
            if(w==endWord){
                return l;
            }
            for(auto it : wordSet){
                if(editDistance(w, it)==1){
                    q.push({l+1,it});
                }
            }
        }
        return 0;
    }
};
