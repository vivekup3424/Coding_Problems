
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    const static int ALPHABET_SIZE = 26;
    struct TrieNode
    {
        struct TrieNode *children[ALPHABET_SIZE];
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
            if (temp->children[index])
            {
                temp->children[index] = new TrieNode();
            }
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
    }
    vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord)
    {
        vector<vector<string>> results;
        struct TrieNode *root = new TrieNode();
        for (const string &word : products)
        {
            insert(root, word);
        }
        int n = searchWord.size();
        for (int i = 0; i < n; i++)
        {
            int index = searchWord[i] - 'a';
            struct TrieNode *temp = root->children[index];
            string result;
            result.push_back(searchWord[i]);
                }
    }
};
int main()
{
}