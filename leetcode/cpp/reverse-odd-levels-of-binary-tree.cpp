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
        //doing a level order traversal
        vector<int> nodes;
        queue<TreeNode*> q;
        q.push(root);
        while(q.size()>0){
            auto top = q.front();
            q.pop();
            nodes.push_back(top->val);
            if(top->left != nullptr){
                q.push(top->left);
            }
            if(top->right != nullptr){
                q.push(top->right);
            }   
        }
        //constructing new Tree from the level order traversal
        TreeNode* newRoot = new TreeNode(nodes[0]);
    }
};