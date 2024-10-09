//NOTE:- lowest common ancestor of a binary search tree
#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
     int val;
 TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };
class solution {
public:
    void dfs(TreeNode *root, TreeNode *source, stack<int> &stk){
        if(root == nullptr || root == source){
            return;
        }
        stk.push(root->left.data)
    }
    TreeNode* lowestcommonancestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //do a dfs to store the path from root to p
    }
};
