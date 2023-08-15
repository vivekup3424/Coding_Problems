
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

class Solution1
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        helper(root, &res);
        return res;
    }
    void helper(TreeNode *root, vector<int> *res)
    {
        if (root == nullptr)
            return;
        helper(root->left, res);
        res->push_back(root->val);
        helper(root->right, res);
    }
    // Time Complexity = O(n) T(n) = 2T(n/2)+1
    // Space COmplexity = O(n)
};
class Solution
{
public: // using stack
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> r;
        helperInorder(root, &r);
        return r;
    }
    void helperInorder(TreeNode *n, vector<int> *r)
    {
        // base case
        if (n == NULL)
            return;
        helperInorder(n->left, r);
        r->push_back(n->val);
        helperInorder(n->right, r);
    }
};
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *newNode(int data)
{
    struct node *Node = (struct node *)malloc(sizeof(struct node));
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    return (Node);
}
void printInorder(struct node *n)
{
    if (n == NULL)
        return; // base case
    // recur on left child
    printInorder(n->left);
    // print the root node
    printf("%d", n->data);
    // recur on right child
    printInorder(n->right);
}