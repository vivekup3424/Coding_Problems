
#include <bits/stdc++.h>
using namespace std;
struct TrieNode
{
    struct TrieNode *children[26];
    bool isEndofWorld;
};
struct TrieNode *getNode()
{
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}
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
    temp->isEndofWorld = true;
}
bool search(struct TrieNode *root, string key)
{
    bool result = true;
    struct TrieNode *temp = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (!temp->children[key[index]])
            return false;
        temp = temp->children[index];
    }
    return true;
}
bool isEmpty(TrieNode *root)
{
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return false;
    return true;
}
// need to understand this further and improve this function
TrieNode *remove(struct TrieNode *root, string key, int depth = 0)
{
    // base cases
    if (root == NULL)
        return root;
    int n = key.size();
    if (depth == n)
    {
        if (root->isEndofWorld == true)
        {
            root->isEndofWorld = false;
        }
        // check if this is not a prefix
        if (isEmpty(root))
        {
            delete root;
            root = NULL;
        }
    }

    // recursive case
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
}
int main()
{
}