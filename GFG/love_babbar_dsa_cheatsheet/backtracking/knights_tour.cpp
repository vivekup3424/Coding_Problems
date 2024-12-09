#include <bits/stdc++.h>
using namespace std;

// Define knight's possible moves
const vector<pair<int, int>> knightMoves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};
int answer[8][8]; // Global array to store the final solution

// Function to copy ChessBoard to answer
void copyBoard(int ChessBoard[8][8], int answer[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            answer[i][j] = ChessBoard[i][j];
        }
    }
}

// Function to perform DFS and solve the Knight's Tour
bool dfs(int x, int y, int ChessBoard[8][8], set<pair<int, int>> &visited) {
    if (visited.size() == 64) {
        // Base case: all cells are visited
        /*copyBoard(ChessBoard, answer); // Copy solution to the global answer*/
        return true;
    }

    // Check bounds and whether cell is already visited
    if (x < 0 || y < 0 || x >= 8 || y >= 8 || visited.count({x, y})) {
        return false;
    }

    // Mark the current cell as visited and update ChessBoard
    visited.insert({x, y});
    ChessBoard[x][y] = visited.size();

    // Explore all possible knight moves
    for (auto move : knightMoves) {
        int nextX = x + move.first;
        int nextY = y + move.second;
        if (dfs(nextX, nextY, ChessBoard, visited)) {
            return true; // Solution found
        }
    }

    // Backtracking: unmark the current cell and reset ChessBoard
    visited.erase({x, y});
    ChessBoard[x][y] = 0;

    return false; // No valid moves from this point
}

int main() {
    // Initialize the ChessBoard
    int ChessBoard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ChessBoard[i][j] = 0;
        }
    }

    // Set to track visited cells
    set<pair<int, int>> visited;

    // Start DFS from the top-left corner
    if (dfs(0, 0, ChessBoard, visited)) {
        // Print the solution from the global answer array
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << setw(3) << answer[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists for the Knight's Tour!" << endl;
    }

    return 0;
}
