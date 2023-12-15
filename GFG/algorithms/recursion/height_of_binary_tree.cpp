
#include <bits/stdc++.h>
using namespace std;
// Find the height of bnary tree

// tree
class node
{
public:
    int data;
    node *left;
    node *right;
};
int maxDepth(node *root)
{
    if (root == NULL)
        return 0;
    int height = max(maxDepth(root->left), maxDepth(root->right));
    return 1 + height; // incrementing the height is important
}
// Helper Function to allocate new node with given data and left and right child as null
node *newNode(int data)
{
    node *Node = new node();
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    return Node;
}
int main()
{
    node *root = newNode(0);
    root->left = newNode(1);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->left->left = newNode(4);
    cout << "Height of the tree = " << maxDepth(root) << endl;
    return 0;
}
// Time complexity  = O(n)
//  Aux Space = O(n)