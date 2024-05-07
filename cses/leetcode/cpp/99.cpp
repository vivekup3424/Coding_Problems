#include <bits/stdc++.h>
using namespace std;
// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void traverseInorder(TreeNode *root, vector<int> &v)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            traverseInorder(root->left, v);
            v.push_back(root->val);
            traverseInorder(root->right, v);
        }
    }
    void dfs(TreeNode *root, unordered_map<int, int> &mp)
    {
        if (root == nullptr)
            return;
        else if (mp.find(root->val) != mp.end())
        {
            root->val = mp[root->val];
        }
        dfs(root->left, mp);
        dfs(root->right, mp);
    }
    void recoverTree(TreeNode *root)
    {
        vector<int> v;
        traverseInorder(root, v);
        // print the vector
        for (auto i : v)
        {
            cout << i << " ";
        }
        cout << endl;
        vector<int> temp = v;
        sort(temp.begin(), temp.end());
        unordered_map<int, int> mp;
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] != v[i])
            {
                mp[v[i]] = temp[i];
            }
        }
        cout << "Printing out the map:=\n";
        for (auto it : mp)
        {
            cout << it.first << ", " << it.second << endl;
        }
        // now doing a typical dfs
    }
    void recoverTree1(TreeNode *root)
    {
        // using the inate property of the tree that
        // root > root->left, root<root->right, and
        // root->left<=root->right
        if (root == nullptr)
        {
            return;
        }
        else if (root->left != nullptr)
        {
            if (root->val < root->left->val)
            {
                int temp = root->val;
                root->val = root->left->val;
                root->left->val = temp;
            }
            recoverTree(root->left);
        }
        else if (root->right != nullptr)
        {
            if (root->val > root->right->val)
            {
                int temp = root->val;
                root->val = root->right->val;
                root->right->val = temp;
            }
        }
    }
};
int main()
{
    TreeNode *root = new TreeNode(3);
    TreeNode *one = new TreeNode(1);
    TreeNode *two = new TreeNode(4);
    TreeNode *three = new TreeNode(2);
    root->left = one;
    root->right = two;
    two->left = three;
    Solution A;
    A.recoverTree(root);
}