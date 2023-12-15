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
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> r;
        helperPostorder(root, &r);
        return r;
    }
    void helperPostorder(TreeNode *root, vector<int> *r)
    {
        if (root == NULL)
            return;
        else
        {
            helperPostorder(root->left, r);
            helperPostorder(root->right, r);
            r->push_back(root->val);
        }
    }
};
int main()
{
}