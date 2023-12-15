
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
    void dfs(TreeNode *root, int depth, int *maxDepth)
    {
        if (root == NULL)
            return;
        *maxDepth = max(*maxDepth, depth);
        dfs(root->left, depth + 1, maxDepth);
        dfs(root->right, depth + 1, maxDepth);
    }
    int findSum(TreeNode *root, int *sum, int depth, int maxDepth)
    {
        if (root == NULL)
            return 0;
        if (depth == maxDepth)
            *sum += root->val;
        findSum(root->left, sum, depth + 1, maxDepth);
        findSum(root->right, sum, depth + 1, maxDepth);
    }
    int deepestLeavesSum(TreeNode *root)
    {
        int maxDepth = 0;
        dfs(root, 0, &maxDepth);
        int sum = 0;
        findSum(root, &sum, 0, maxDepth);
        return sum;
    }
};
int main()
{
}