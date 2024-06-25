#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Definition for a binary tree node.*/
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
    void recurse(TreeNode *root, int &sum)
    {
        if (root == nullptr)
        {
            return;
        }
        recurse(root->right, sum);
        sum += root->val;
        root->val = sum;
        recurse(root->left, sum);
    }
    TreeNode *bstToGst(TreeNode *root)
    {
        int sum = 0;
        recurse(root, sum);
        return root;
    }
};