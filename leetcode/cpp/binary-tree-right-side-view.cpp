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
    vector<int> rightSideView(TreeNode* root) {
        if(root==nullptr){
            return {};
        }
        queue<pair<int,TreeNode*>> q;
        map<int,int> mp;
        q.push({0,root});
        while(q.size()>0){
            auto [l,node] = q.front();
            q.pop();
            mp[l] = node->val;
            if(node->left != nullptr){
                q.push({l+1,node->left});
            }
            if(node->right != nullptr){
                q.push({l+1,node->right});
            }
        }
        vector<int> v;
        for(auto it: mp){
            v.push_back(it.second);
        }
        return v;
    }
};
