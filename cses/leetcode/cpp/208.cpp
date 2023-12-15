
#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE = 26;
class Trie
{
private:
    Trie *children[ALPHABET_SIZE];
    bool isEndOfWord;

public:
    Trie()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
        }
        isEndOfWord = false;
    }

    void insert(string word)
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

    bool search(string word)
    {
        Trie *temp = this;
        for (char c : word)
        {
            if (temp->children[c - 'a'] == NULL)
                return false;
            temp = temp->children[c - 'a'];
        }
        return temp->isEndOfWord;
    }

    bool startsWith(string prefix)
    {
        Trie *temp = this;
        for (auto c : prefix)
        {
            if (temp->children[c - 'a'] == NULL)
                return false;
            temp = temp->children[c - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
int main()
{
}