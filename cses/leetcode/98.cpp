// 98. Validate Binary Search Tree

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
    bool isValidBST(TreeNode *root)
    {
        return helper(root, LLONG_MIN, LLONG_MAX);
    }
    bool helper(TreeNode *root, long long low, long long high)
    {
        if (!root)
            return true;
        else if (!(low < root->val and root->val < high))
            return false;

        return (helper(root->left, low, root->val) and
                helper(root->right, root->val, high));
    }
};
int main()
{
}