#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

bool isMaxHeap(struct Node *root)
{
    if (root == nullptr)
    {
        return true; // A null tree is a valid max-heap
    }
    // Check if left child is greater than root
    if (root->left != nullptr && root->left->data > root->data)
    {
        return false;
    }
    // Check if right child is greater than root
    if (root->right != nullptr && root->right->data > root->data)
    {
        return false;
    }
    // Recursively check the left and right subtrees
    return isMaxHeap(root->left) && isMaxHeap(root->right);
}

int main()
{
    // Example usage:
    Node *root = new Node(1);
    root->left = new Node(5);
    root->right = new Node(3);
    root->left->left = new Node(2);
    root->left->right = new Node(1);

    if (isMaxHeap(root))
    {
        cout << "The tree is a max-heap" << endl;
    }
    else
    {
        cout << "The tree is not a max-heap" << endl;
    }

    return 0;
}
