// NOTE:- lowest common ancestor of a binary search tree
#include <bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution
{
public:
    void dfs(TreeNode *root, TreeNode *source, stack<int> &stk)
    {
        if (root == nullptr)
        {
            return;
        }
        stk.push(root->val);
        if (root->val == source->val)
        {
            return;
        }
        dfs(root->left, source, stk);
        dfs(root->right, source, stk);
        stk.pop();
        return;
    }
    TreeNode *lowestcommonancestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        stack<int> stk;
        dfs(root,p,stk);
        printf("path from %d to %d is:\t",root->val,p->val);
        while(!stk.empty()){
            printf("%d, ",stk.top());
            stk.pop();
        }
    }
};
