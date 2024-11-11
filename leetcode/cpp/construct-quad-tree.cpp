#include <bits/stdc++.h>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* constructTreeNode(vector<vector<int>> &grid, int x1, int x2, int y1, int y2) {
        int count0 = 0, count1 = 0;
        for(int i = x1; i < x2; i++) {
            for(int j = y1; j < y2; j++) {
                if(grid[i][j] == 0) count0++;
                else count1++;
            }
        }

        // Check if the current region is uniform
        if(count0 == 0) {
            return new Node(1, true);
        } else if(count1 == 0) {
            return new Node(0, true);
        } else {
            // The node is not a leaf, so it has four children
            Node* newNode = new Node(0, false);
            int midx = (x1 + x2) / 2;
            int midy = (y1 + y2) / 2;
            
            // Recursively divide the grid into four quadrants
            newNode->topLeft = constructTreeNode(grid, x1, midx, y1, midy);
            newNode->topRight = constructTreeNode(grid, x1, midx, midy, y2);
            newNode->bottomLeft = constructTreeNode(grid, midx, x2, y1, midy);
            newNode->bottomRight = constructTreeNode(grid, midx, x2, midy, y2);
            
            return newNode;
        }
    }

    Node* construct(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        return constructTreeNode(grid, 0, rows, 0, cols);
    }
};
