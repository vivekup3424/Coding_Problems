/**
 * Definition for a binary tree node.*/
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
    void dfs(TreeNode *root, int depth, int &max_depth)
    {
        max_depth = max(depth, max_depth);
        if (root == nullptr)
            return;
        else
        {
            dfs(root->left, depth + 1, max_depth);
            dfs(root->right, depth + 1, max_depth);
        }
        return;
    }
    vector<int> rightSideView(TreeNode *root)
    {
        // first get the depth of tree
        int max_depth = 0;
        dfs(root, 0, max_depth);
        cout << "Depth = " << max_depth << endl;
        // now keeping max_depth in mind, construct a queue
        queue<pair<TreeNode *, int>> q; //{node,level}
        vector<int> rightView(max_depth, -101);
        // do a bfs
        q.push({root, 0});
        while (q.empty() == false)
        {
            TreeNode *node = q.front().first;
            int depth = q.front().second;
            q.pop();
            if (rightView[depth] == -101)
            {
                rightView[depth] = node->val;
            }
            if (node->left != nullptr)
            {
                q.push({node->left, depth + 1});
            }
            if (node->right != nullptr)
            {
                q.push({node->right, depth + 1});
            }
        }
        // print the resultant vector
        for (auto it : rightView)
        {
            cout << it << " ";
        }
        cout << endl;
        return rightView;
    }
};