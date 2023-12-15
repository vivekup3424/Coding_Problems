#include <bits/stdc++.h>
using namespace std;
template <typename T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    ~TreeNode()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

void storeNodes(TreeNode<int> *root, unordered_set<set> &nodes,
                unordered_set<int> &leafNodes)
{
    if (root == nullptr)
        return;
    else if (root->left == nullptr and root->right == nullptr)
    {
        leafNodes.insert(root->data);
    }
    nodes.insert(root->data);
    storeNodes(root->left, nodes, leafNodes);
    storeNodes(root->right, nodes, leafNodes);
}
bool isDeadEnd(TreeNode<int> *root)
{
    // traverse the tree, and for each leaf node n,
    // check whether n-1 or n+1 already exists inside the tree
    // if this exists, then this is leaf node is a dead-end
    // because we can't insert node as further in that
    unordered_set<int> nodes;
    unordered_set<int> leafNodes;

    // let's do a inorder traversal and store the nodes
    nodes.insert(0); // handles edge case of leaf node 1
    for (auto it : leafNodes)
    {
        if (nodes.count(it - 1) || nodes.count(it + 1))
        {
            return true;
        }
    }
    return false;
}