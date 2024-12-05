// Given a N*N board with the Knight placed on the first block of an empty board.
// Moving according to the rules of chess knight must visit each square exactly once.
// Print the order of each cell in which they are visited.

#include <bits/stdc++.h>
using namespace std;
void dfs(int x, int y, int ChessBoard[8][8], bool visited[8][8]){
    if(visited[x][y] == true || x < 0 || y < 0 || x >= 8 || y >= 8){
        return;
    }
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
    int N = 8;
    int Solution[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Solution[i][j] = 0;
        }
    }
}
