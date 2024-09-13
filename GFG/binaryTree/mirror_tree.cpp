#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val){
        this->data = val;
        left = NULL;
        right = NULL;
    }
};

class Solution{
public:
    void mirror(Node *root){
        if(root==nullptr){
            return;
        }
        auto *temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirror(root->left);
        mirror(root->right);
        return;
    }
};
