
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
    int minDepth(TreeNode *root)
    {
        // base case
        if (root == NULL)
            return 0;
        // recursive case
        int leftDepth = minDepth(root->left);
        int rightDepth = minDepth(root->right);
        if (leftDepth == 0) // check for null cases
            return rightDepth + 1;
        if (rightDepth == 0)
            return leftDepth + 1;
        return min(leftDepth, rightDepth) + 1;
    }
    // time-complexity : O(n), n = num of nodes in the tree
    // space-complexity : O(h), h = height of the tree :- worst case : O(n), when tree is skewed
    // best case : O(logn) for a balanced tree
};
main()
{
}