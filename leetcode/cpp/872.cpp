
#include <bits/stdc++.h>
using namespace std;
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
    void dfs(TreeNode *root, vector<int> &l1)
    {
        if (root == NULL)
            return;
        else if (root->left == nullptr and root->right == nullptr)
        {
            l1.push_back(root->val);
            return;
        }
        else
        {
            dfs(root->left, l1);
            dfs(root->right, l1);
        }
    }
    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        // two trees can be similar if their leaf nodes order we get doing inorder traversal is similar
        vector<int> l1, l2;
        dfs(root1, l1);
        dfs(root2, l2);
        if (l1 == l2)
            return true;
        else
            return false;
    }
};
int main()
{
}