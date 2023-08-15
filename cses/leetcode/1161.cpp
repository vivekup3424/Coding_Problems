#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Method 1 :- Using BFS(level order traversal)
class Solution
{
public:
    int height(struct TreeNode *root)
    {
        // base cases
        if (root == NULL)
            return 0;
        // recursion
        else
            return (1 + max(height(root->left), height(root->right)));
    }
    int currentLevelSum(struct TreeNode *root, int level) // sum of nodes of that level
    {
        // base case
        if (root == NULL)
            return 0;
        if (level == 1)
            return root->val;
        else if (level > 0)
            return currentLevelSum(root->left, level - 1) + currentLevelSum(root->right, level - 1); // beware of stack-overflow
        return 0;
    }
    int maxLevelSum(TreeNode *root)
    {
        int h = height(root);
        int maxSum = INT_MIN;
        vector<int> dp(h + 1, 0); // to store sum
        for (int i = 1; i < h + 1; i++)
        {
            dp[i] = currentLevelSum(root, i);
            maxSum = max(maxSum, dp[i]);
        }
        for (int i = 0; i < h + 1; i++)
        {
            if (dp[i] == maxSum)
            {
                return i;
                break;
            }
        }
        return 0;
    }
};

// practice for level order traversal of binary tree
// BFS uses queue

// Method 1
// Algo:-
/*
1.Find the height of tree
2. Then for each level, run a recursive function by maintaining
current height. Whenever the level of a node matches, print that node
*/
/*
void printLevelOrder(struct TreeNode *root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++)
    {
        printCurrentLevel(root, i);
    }
}
void printCurrentLevel(struct TreeNode *root, int level) // prints all the node for that level
{
    if (root == NULL)
        return;
    if (level == 1) // base case
        cout << root->val;
    else if (level > 1)
    {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
int height(struct TreeNode *node) // returns the
{
    if (node == NULL)
        return 0;
    else
    {
        int lheight = height(node->left);
        int rheight = height(node->right);
        return 1 + max(lheight, rheight);
    }
}*/
// this above method is good for our question
// Driver code
int main()
{
    // Test case: [1, 2, 3]
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    Solution sol;
    int maxLevel = sol.maxLevelSum(root);
    std::cout << "Maximum level with the maximum sum: " << maxLevel << std::endl;

    return 0;
}

// IMPORTANT

// implement the above program using dp or using queue
