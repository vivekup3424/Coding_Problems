#include <bits/stdc++.h>
#include <queue>
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
    long long kthLargestLevelSum(TreeNode* root, int k) {
      queue<pair<int,TreeNode*>> q;
    q.push({0,root});
    map<int,long long> sum;
    while(q.size()>0){
      auto [l,node] = q.front();
      q.pop();
      sum[l] += (long long)node->val;
      if(node->left != nullptr){
        q.push({l+1,node->left});
      }
      if(node->right != nullptr){
        q.push({l+1,node->right});
      }
    }
    priority_queue<int,vector<int>,greater<int>> maxHeap;
    for(auto it: sum){
      maxHeap.push(it.second);
      if(maxHeap.size()>k){
        maxHeap.pop();
      }
    }
    return maxHeap.top();
    }
};
