#include <bits/stdc++.h>
using namespace std;
// NOTE :- TreeNode given on leetcode
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(nullptr), right(nullptr){}
    TreeNode(int v):val(v), left(nullptr), right(nullptr){}
};

class Solution{
    TreeNode *invertTree(TreeNode *root){
        if(root==nullptr)return root;
        TreeNode *temp = invertTree(root->left);
        root->left = invertTree(root->right);
        root->right = root->left;
    }
}
