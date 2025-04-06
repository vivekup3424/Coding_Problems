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
    bool dfs(TreeNode *root, TreeNode *source, deque<TreeNode*> &dq)
    {
        if (root == nullptr)
        {
            return false;
        }
        dq.push_back(root);
        if (root->val == source->val)
        {
            return true;
        }
        if (dfs(root->left, source, dq) || dfs(root->right, source, dq))
        {
            return true;
        }
        dq.pop_back();
        return false;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        deque<TreeNode*> dq1;
        dfs(root, p, dq1);
        deque<TreeNode*> dq2;
        dfs(root, q, dq2);
        TreeNode* answerNode = nullptr;
        while(dq1.front()==dq2.front()){
            answerNode = dq1.front();
            dq1.pop_front();
            dq2.pop_front();
        }
        return answerNode;
    }
};