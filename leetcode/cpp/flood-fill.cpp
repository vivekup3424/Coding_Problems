#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        vector<vector<int>> answer = image;
        if(image[sr][sc]==color){
            return answer;
        }
        vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};
        queue<pair<int,int>> q;
        q.push({sr,sc});
        int prevColor = image[sr][sc]
        answer[sr][sc] = color;
        for(auto [x,y] : directions){
            auto [nodeX,nodeY] = q.front();
            q.pop();
            auto neighborX = nodeX + x;
            auto neighborY = nodeY + y;
            if(image[nodeX][nodeY]==image[])
        }
    }
};