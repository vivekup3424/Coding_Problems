// longest word with all prefixes

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    struct TrieNode
    {
        struct TrieNode *children[26];
        bool isEndOfWords;
        TrieNode()
        {
            for (int i = 0; i < 26; i++)
            {
                this->children[i] = NULL;
            }
            this->isEndOfWords = false;
        }
    };
    void insert(struct TrieNode *root, string key)
    {
        int n = key.size();
        if (root == NULL)
        {
            root = new TrieNode();
        }
        struct TrieNode *temp = root;
        for (int i = 0; i < n; i++)
        {
            int index = key[i] - 'a';
            temp->children[i] = new TrieNode();
            temp = temp->children[i];
        }
        temp->isEndOfWords = true;
    }
    bool isEmpty(TrieNode *root)
    {
        for (int i = 0; i < 26; i++)
            if (root->children[i])
                return false;
        return true;
    }
    string longestWord(vector<string> &words)
    {
        struct TrieNode *root = new TrieNode();
        int n = words.size();
        for (int i = 0; i < n; i++)
        {
            insert(root, words[i]);
        }
    }
    string returnWord(struct TrieNode *root, string result, int depth, string longest)
    {
        // base case
        if (root == nullptr)
            return "";
        string longest = "";
        if (longest.size() > result.size())
            longest = result;
        if (isEmpty(root) and root->isEndOfWords)
            return longest;
        struct TrieNode *temp = root;
        for (int i = 0; i < 26; i++)
        {
            if (temp->children[i] != NULL and temp->children[i]->isEndOfWords == true)
            {
                returnWord(temp, result + (char)(i + 'a'), depth + 1, longest);
                temp = temp->children[i];
            }
        }
        return longest;
    }
};
int main()
{
}