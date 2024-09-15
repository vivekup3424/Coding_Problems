#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};
struct DLL
{
    int data;
    struct DLL *next;
    struct DLL *prev;
};
// This function should return head to the DLL
class Solution
{
public:
    Node *inorder(Node *root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        inorder(root->left);
        auto temp = new Node(root->data);
        inorder(root->right);
        return temp;
    }
    Node *bToDLL(Node *root)
    {
    }
};
