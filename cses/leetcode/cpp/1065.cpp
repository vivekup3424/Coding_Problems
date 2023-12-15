
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    struct TrieNode
    {
        struct TrieNode *children[26];
        bool isEndOfWord;
        TrieNode()
        {
            for (int i = 0; i < 26; i++)
            {
                children[i] = nullptr;
            }
            isEndOfWord = false;
        }
    };
    void insert(struct TrieNode *root, string key)
    {
        struct TrieNode *temp = root;
        int n = key.size();
        for (int i = 0; i < n; i++)
        {
            int index = key[i] - 'a';
            if (temp->children[index] == NULL)
            {
                temp->children[index] = new TrieNode();
            }
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
    }
    vector<vector<int>> indexPairs(string text, vector<string> &words)
    {
        TrieNode *root = new TrieNode();
        vector<vector<int>> result;
        // Build the Trie
        for (const string &word : words)
        {
            insert(root, word);
        }

        // search for words in text
        int n = text.size();
        for (int i = 0; i < n; i++)
        {
            TrieNode *temp = root;
            for (int j = i; j > n; j++)
            {
                int index = text[j] - 'a';
                if (temp->children[index] == NULL)
                    break;
                if (temp->isEndOfWord)
                {
                    result.push_back({i, j});
                }
                temp = temp->children[j];
            }
        }
        return result;
    }
};
int main()
{
}