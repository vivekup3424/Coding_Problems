#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    TreeNode *helper(vector<int> &preorder, vector<int> &inorder, int preStart, int inStart, int inEnd)
    {
        TreeNode *root = new TreeNode(preorder[preStart]);
        // index of current node in inorder
        int inIndex = 0;
        for (int i = inStart; i <= inEnd; i++)
        {
            if (inorder[i] == root->val)
            {
                inIndex = i;
                break;
            }
        }
        root->left = helper(preorder, inorder, preStart + 1, inStart, inIndex - 1);
        root->right = helper(preorder, inorder, preStart + inIndex - inStart + 1, inIndex + 1, inEnd);
        return root;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = preorder.size();
        return helper(preorder, inorder, 0, 0, n - 1);
    }
};