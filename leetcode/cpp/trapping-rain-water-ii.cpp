#include <bits/stdc++.h>
using namespace std;

struct Node{
    int x, y, h;
    Node(int _x, int _y, int _h) : x(_x), y(_y), h(_h) {}
};

class Solution {
    public:
    int trapRainWater(vector<vector<int>> &heightMap){
        int rows = heightMap.size();
        int cols = heightMap[0].size();
        if(rows < 3 || cols < 3) return 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        priority_queue<Node, vector<Node>, [](Node &a, Node &b){
            return a.h > b.h;
        }> minHeap;
    }
}