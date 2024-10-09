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
    int dfs(TreeNode *root, int &maxSum){
        if(root==nullptr){
            return 0;
        }
        int leftSum = dfs(root->left, maxSum);
        int rightSum = dfs(root-right, maxSum);
        int maxi = max(leftSum + root->val, rightSum + root-val, leftSum+rightSum+root->val);
        maxSum = max(maxi, maxSum);
        if(maxi < leftSum and maxi < rightSum){
            return 0;
        }else{
            return maxi;
        }
    }
    int maxPathSum(TreeNode* root) {

    }
};

int main(){

}
