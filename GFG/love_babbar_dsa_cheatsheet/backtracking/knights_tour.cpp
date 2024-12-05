// Given a 8*8 board with the Knight placed on the first block of an empty board.
// Moving according to the rules of chess knight must visit each square exactly once.
// Print the order of each cell in which they are visited.

#include <bits/stdc++.h>
using namespace std;
void dfs(int x, int y, int ChessBoard[8][8], set<pair<int,int>> visited){
    if((visited.count({x,y}) and visited.size()<64) || x < 0 || y < 0 || x >= 8 || y >= 8){
        visited.erase({x,y});
        ChessBoard[x][y]  = 0;
        return;
    }
    visited.insert({x,y});
    ChessBoard[x][y] = visited.size();
    dfs(x + 2, y + 1, ChessBoard, visited);
    dfs(x + 2, y - 1, ChessBoard, visited);
    dfs(x - 2, y + 1, ChessBoard, visited);
    dfs(x - 2, y - 1, ChessBoard, visited);
    dfs(x + 1, y + 2, ChessBoard, visited);
    dfs(x + 1, y - 2, ChessBoard, visited);
    dfs(x - 1, y + 2, ChessBoard, visited);
    dfs(x - 1, y - 2, ChessBoard, visited);
}
int main(){
    int Solution[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Solution[i][j] = 0;
        }
    }
    set<pair<int,int>> visited;
    dfs(0,0,Solution,visited);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << Solution[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
