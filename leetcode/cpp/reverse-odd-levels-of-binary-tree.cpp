#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(root == nullptr){
            return root;
        }
        auto temp = root->left;
        root->left = root->right;
        root->right = temp;
        reverseOddLevels(root->left);
        reverseOddLevels(root->right);
        return root;
    }
};