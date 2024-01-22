#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
     TreeNode *left;
     int val;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
class Solution {
private:
    //returns an adjacency list
    unordered_map<int, vector<int>> createGraph(TreeNode *root){
        //do a bfs traversal and create the graph
        queue<pair<int,int>> q; //stores the edges of the tree 
        unordered_map<int,vector<int>> adjList;
        if(root == nullptr)return 
    }
public:

    int amountOfTime(TreeNode* root, int start) {
        //convert the tree to graph, 
        //then do bfs to get the node with maximum distance from the start node


    }
};