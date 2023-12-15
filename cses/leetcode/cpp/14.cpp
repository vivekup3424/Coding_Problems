
#include <bits/stdc++.h>
using namespace std;
struct TrieNode
{
    TrieNode *children[26];
    bool isEndOfWord;
    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        isEndOfWord = false;
    }
};
class Solution
{
public:
    void insert(TrieNode *root, string s)
    {
        struct TrieNode *temp = root;
        for (char c : s)
        {
            int i = c - 'a';
            if (!temp->children[i])
            {
                temp->children[i] = new TrieNode();
            }
            temp = temp->children[i];
        }
        temp->isEndOfWord = true;
    }
    void dfs(TrieNode *root, string &prefix, string &ans)
    {
        if (root == NULL || root->isEndOfWord)
            return;
        int count = 0;
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i])
            {
                count++;
            }
        }
        if (count > 1)
            return;
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i])
            {
                prefix.push_back(i + 'a');
                if (prefix.size() > ans.size())
                {
                    ans = prefix;
                }
                dfs(root->children[i], prefix, ans);
                prefix.pop_back();
            }
        }
    }
    string longestCommonPrefix(vector<string> &strs)
    {
        int maxLength = -1;
        TrieNode *root = new TrieNode();
        for (string s : strs)
        {
            insert(root, s);
        }
        string prefix = "", ans = "";
        dfs(root, prefix, ans);
        return ans;
    }
};
int main()
{
    Solution sol;

    // Test case 1: Regular strings with common prefix "flow"
    vector<string> strs1 = {"flower", "flow", "flight"};
    cout << "Test Case 1: " << sol.longestCommonPrefix(strs1) << endl;

    // Test case 2: Empty input
    vector<string> strs2;
    cout << "Test Case 2: " << sol.longestCommonPrefix(strs2) << endl;

    // Test case 3: Single string
    vector<string> strs3 = {"leetcode"};
    cout << "Test Case 3: " << sol.longestCommonPrefix(strs3) << endl;

    // Test case 4: No common prefix
    vector<string> strs4 = {"dog", "car", "race"};
    cout << "Test Case 4: " << sol.longestCommonPrefix(strs4) << endl;

    // Test case 5: Strings with common prefix at the end
    vector<string> strs5 = {"interview", "overview", "preliminary"};
    cout << "Test Case 5: " << sol.longestCommonPrefix(strs5) << endl;

    // Test case 6: Mix of empty and non-empty strings
    vector<string> strs6 = {"", "apple", "", "application"};
    cout << "Test Case 6: " << sol.longestCommonPrefix(strs6) << endl;

    // Test case 7: Large input
    vector<string> strs7 = {"abcdefgh", "abcdklmn", "abcdpqrs"};
    cout << "Test Case 7: " << sol.longestCommonPrefix(strs7) << endl;

    return 0;
}