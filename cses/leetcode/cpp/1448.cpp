// just do a dfs traversal, and pass max_so_far value and counter pointer, max_so_far intially is -inf
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
    void dfs(TreeNode *root, int &count, int maxValue)
    {
        if (root == nullptr)
            return;
        else
        {
            if (root->val >= maxValue)
                count++;
            maxValue = max(maxValue, root->val);
            dfs(root->left, count, maxValue);
            dfs(root->right, count, maxValue);
        }
    }
    int goodNodes(TreeNode *root)
    {
        int count = 0, maxValue = INT_MIN;
        dfs(root, count, maxValue);
        return count;
    }
};
int main()
{
}