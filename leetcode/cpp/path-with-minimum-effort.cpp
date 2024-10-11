/*
# Path With Minimum Effort Problem

## Problem Description

You are a hiker planning a route through a mountainous 
terrain.

### Given:
- A 2D array `heights` of size `rows x columns`
- `heights[row][col]` shows height at cell (row, col)
- Start position: top-left cell (0, 0)
- End position: bottom-right cell (rows-1, columns-1)
- All positions use 0-based indexing

### Movement Rules:
You can move in four directions:
- Up
- Down 
- Left
- Right

### Effort Calculation:
- For any route, calculate absolute height differences
  between consecutive cells
- Route's effort = maximum of these differences

### Goal:
Find the route requiring minimum effort to reach the 
destination.

### Required Output:
Return the minimum effort value needed to travel from
start to end.

### Notes:
- A route consists of sequence of connected cells
- Compare heights of cells you move between
- Find path that minimizes maximum height difference
*/

#include <bits/stdc++.h>
using namespace std;

// Node class used for the priority queue
class Node {
public:
    int maxDiff;
    int x;
    int y;
    Node(int d, int x, int y) : maxDiff(d), x(x), y(y) {}
    
    // Overloading the () operator to create a min-heap based on maxDiff
    bool operator()(Node &A, Node &B) {
        return A.maxDiff > B.maxDiff;
    }
};

class Solution {
public:
    // Directions: up, right, down, left
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    int minEffortPathDijkstraApproach(vector<vector<int>>& heights) {
        int r = heights.size(), c = heights[0].size();
        vector<vector<int>> dist(r, vector<int>(c, INT_MAX));  // Distance matrix
        priority_queue<Node, vector<Node>, Node> pq;  // Min-heap

        // Start from top-left corner (0, 0)
        pq.push(Node(0, 0, 0));
        dist[0][0] = 0;

        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();

            int d = curr.maxDiff, x = curr.x, y = curr.y;
            
            // If we reach the bottom-right corner, return the effort
            if (x == r - 1 && y == c - 1) return d;

            // Explore all four directions
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                // Check if the new position is within bounds
                if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                    // Calculate new effort (maximum of the current effort and the height difference)
                    int newEffort = max(d, abs(heights[nx][ny] - heights[x][y]));
                    // If the new effort is less than the previously recorded effort for this cell
                    if (newEffort < dist[nx][ny]) {
                        dist[nx][ny] = newEffort;
                        pq.push(Node(newEffort, nx, ny));  // Add new node to the priority queue
                    }
                }
            }
        }

        return 0;  // This line will never be reached in a valid case
    }
};
