
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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == NULL)
            return false;
        /*
        I dont know why this is not working
        if (targetSum == 0)
            return true;
        */
        // Check if we have reached a leaf node
        if (root->left == nullptr && root->right == nullptr)
        {
            return targetSum == root->val; // Compare remaining targetSum with leaf value
        }
        // recursive case
        bool left = hasPathSum(root->left, targetSum - root->val);
        bool right = hasPathSum(root->right, targetSum - root->val);
        return left or right;
    }
};
int main()
{
}