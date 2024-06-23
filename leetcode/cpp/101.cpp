
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
    bool isSymmetric(TreeNode *root)
    {
        if (root == NULL)
            return true;
        return isMirror(root->left, root->right);
    }
    bool isMirror(TreeNode *left, TreeNode *right)
    {
        if (left == NULL and right == NULL)
            return true;
        else if ((left == NULL and right != NULL) or (left != NULL and right == NULL))
            return false;
        else if (left->val != right->val)
            return false;
        else
            return isMirror(left->left, right->right) and isMirror(left->right, right->left);
    }
};
int main()
{
}