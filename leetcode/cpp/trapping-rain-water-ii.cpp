#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    int x, y, h;
    node(int _x, int _y, int _h) : x(_x), y(_y), h(_h) {};
    bool operator<(const node &b) const {
        return h > b.h;
    }
}Node;

class Solution {
    public:
    int trapRainWater(vector<vector<int>> &heightMap){
        int rows = heightMap.size();
        int cols = heightMap[0].size();
        if(rows < 3 || cols < 3) return 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        priority_queue<Node, vector<Node>, greater<Node>> minHeap;
        int totalWater = 0;
        for(int i = 0; i < rows; i++){
            minHeap.push(Node(i, 0, heightMap[i][0]));
            minHeap.push(Node(i, cols - 1, heightMap[i][cols - 1]));
            visited[i][0] = true;
            visited[i][cols - 1] = true;
        }
        for(int j = 1; j < cols - 1; j++){
            minHeap.push(Node(0, j, heightMap[0][j]));
            minHeap.push(Node(rows - 1, j, heightMap[rows - 1][j]));
            visited[0][j] = true;
            visited[rows - 1][j] = true;
        }
        vector<int> dirX = {0, 0, 1, -1};
        vector<int> dirY = {1, -1, 0, 0};
        while(!minHeap.empty()){
            auto node = minHeap.top();
            minHeap.pop();
            for(int i = 0; i < 4; i++){
                auto neighborX = node.x + dirX[i];
                auto neighboxY = node.y + dirY[i];
                if(0 < neighborX && neighborX < rows &&
                    0 < neighboxY && neighboxY < cols && 
                    !visited[neighborX][neighboxY]){
                        auto neighborHeight = heightMap[neighborX][neighboxY];
                        if(neighborHeight < node.h){
                            totalWater += (node.h - neighborHeight);
                        }
                        auto newHeight = max(node.h, neighborHeight);
                        visited[neighborX][neighboxY] = true;
                        minHeap.push({neighborX,neighboxY,neighborHeight});
                    }
            }
        }
        return totalWater;
    }
};