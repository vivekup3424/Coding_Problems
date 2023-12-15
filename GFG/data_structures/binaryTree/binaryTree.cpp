#include <bits/stdc++.h>
using namespace std;
/*Binary Tree Representation in C: A tree is represented 
by a pointer to the topmost node in tree. 
If the tree is empty, then value of root is NULL. 
A Tree node contains following parts. 
1. Data 
2. Pointer to left child 
3. Pointer to right child
In C, we can represent a tree node using structures. 
Below is an example of a tree node with an integer data.*/
class Node
{
    public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};
int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    /* 4 becomes left child of 2
               1
            /     \
           2       3
          / \     / \
         4  NULL NULL NULL
        / \
     NULL NULL
    */
   

}