
#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
const int ALPHABETS_SIZE = 26;

class Trie
{
public:
    Trie *children[26];
    bool isEndOfWord;
    Trie()
    {
        for (int i = 0; i < ALPHABETS_SIZE; i++)
        {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }

    void insert(std::string word)
    {
        Trie *temp = this;
        for (char c : word)
        {
            if (temp->children[c - 'a'] == NULL)
                temp->children[c - 'a'] = new Trie();
            temp = temp->children[c - 'a']; // move to the next node, going deeper
        }
        temp->isEndOfWord = true;
    }
};
void searchLCP(Trie *P, string &current_prefix, string &longestPrefix)
{
    for (int i = 0; i < ALPHABETS_SIZE; i++)
    {
        if (P->children[i] != nullptr and P->children[i]->isEndOfWord == true)
        {
            current_prefix.push_back(i + 'a');
            longestPrefix = max(current_prefix, longestPrefix);
            searchLCP(P->children[i], current_prefix, longestPrefix);
            current_prefix.pop_back();
        }
    }
}
std::string completeString(int n, vector<string> &a)
{
    Trie *P = new Trie();
    for (string &s : a)
    {
        P->insert(s);
    }
    string current_prefix = "", longest_prefix = "";
    searchLCP(P, current_prefix, longest_prefix);
    return longest_prefix != "" ? longest_prefix : "None";
}
