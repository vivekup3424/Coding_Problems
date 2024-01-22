#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end()); //set of strings, duh :|
    queue<pair<string, int>> q;
    int distance = 1;
    q.push({beginWord,distance});
    while (q.empty()==false)
    {
        string word = q.front().first;
        int dist = q.front().second;
        q.pop();
        if(word == endWord)return dist;
        //remove the word from the dict, so I dont go back
        dict.erase(word);
        for(int i = 0; i < word.size(); i++){
            //changing every letter of the word
            string temp = word;
            for(int j = 0; j < 26; j++){
                temp[i] = 'a' + j;
                if(dict.count(temp)){
                    q.push({temp, dist+1});
                }
            }
        }
    }
    return -1;
    }
};
int main(){
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    Solution *A = new Solution();
    A->ladderLength(beginWord, endWord, wordList);
}