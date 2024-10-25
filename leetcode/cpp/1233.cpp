#include <bits/stdc++.h>
using namespace std;

class TrieNode{
public:
    map<string,TrieNode*> children;
    bool isEndOfWord;
    TrieNode():isEndOfWord(false){}
    ~TrieNode(){
        for(auto it : children){
            delete it.second;
        }
    }
};
class Trie{
private:
    TrieNode *root;
public:
    Trie(){
        root = new TrieNode();
    }
    void addWord(string word){
        vector<string> folders;
        string temp;
        for(auto c : word){
            if(c=='/'){
                if(temp.size()>0){
                    folders.push_back(temp);
                }
                temp = "";
            }else{
                temp.push_back(c);
            }
        }
        if(temp.size()>0){
            folders.push_back(temp);
        }
        TrieNode *current = root;
        for(auto directory : folders){
            if(root->children.find(directory)==root->children.end()){
                current->children[directory] = new TrieNode();
            }
            current = current->children[directory];
        }
        current->isEndOfWord = true;
    }
    int numDirectories(){
        queue<TrieNode*> q;
        int count = 0;
        q.push(root);
        while(q.size()>0){
            auto node = q.front();
            q.pop();
            if(node->isEndOfWord){
                count++;
            }
            else{
                for(auto it : node->children){
                    q.push(it.second);
                }
            }
        }
        return count;
    }
    ~Trie(){
        delete root;
    }
};

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folders) {
        auto fileSystem = new Trie();
        for(auto folder : folders)
    }
};
