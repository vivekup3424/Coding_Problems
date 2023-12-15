
#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE = 26;
struct TrieNode
{
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};
void insert(TrieNode *root, string s)
{
    TrieNode *temp = root;
    for (char c : s)
    {
        int index = c - 'a';
        if (temp->children[index] == nullptr)
            temp->children[index] = new TrieNode();
        temp = temp->children[index];
    }
    temp->isEndOfWord = true;
}
int leftover(TrieNode *root, string s)
{
    TrieNode *temp = root;
    int i = 0;
    for (i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        if (temp->children[index] == nullptr)
            break;
        temp = temp->children[index];
    }
    return s.length() - i;
}
// Method 1:- Unsuccesful. I fucked up here.
class Solution1
{
public:
    int minExtraChar(string s, vector<string> &dictionary)
    {
        TrieNode *root = new TrieNode();
        for (int i = 0; i < dictionary.size(); i++) // building up the trie
            insert(root, dictionary[i]);
        int n = s.length();
        int dp[n + 1];
        TrieNode *temp = root;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[i] = leftover(root, s.substr(0, i));
            }
            else
            {
                dp[i] = min(dp[i - 1] + 1, leftover(root, s.substr(0, i)));
            }
        }
        delete root;
        return dp[n - 1];
    }
};
class Solution
{
public:
    int minExtraChar(string s, vector<string> &dictionary)
    {
        TrieNode *root = new TrieNode();
        for (int i = 0; i < dictionary.size(); i++) // building up the trie
            insert(root, dictionary[i]);
        int minUnsedChars = 0, i = 0;
        TrieNode *temp = root;
        int n = s.length();
        int dp[n + 1];
        while (i < s.length())
        {
            char c = s[i];
            int index = c - 'a';
            if (i == 0)
            {
                if (temp->children[index] == NULL)
                {
                    dp[i] = 1;
                }
                else
                {
                    dp[i] = 0;
                    temp = temp->children[index];
                }
            }
            else
            {
                if (temp->children[index] == NULL)
                {
                    i++;
                    dp[i] = dp[i - 1] + 1;
                    temp = root; // going back to root
                }
                else
                {
                    if (temp->children[index]->isEndOfWord)
                    {
                        temp = root; // going back to root
                    }
                    else
                    {
                        temp = temp->children[index]; // going to the next node, going deeper
                    }
                    i++;
                }
            }
        }
        return minUnsedChars;
    }
};
int main()
{
    string s = "leetscode";
    vector<string> dictionary = {"leet", "code"};
    Solution obj;
    cout << obj.minExtraChar(s, dictionary);
}