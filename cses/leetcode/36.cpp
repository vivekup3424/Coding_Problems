class Solution {
    private:
    bool isValidInRow(vector<vector<char>>& board, int row, int num) {
    unordered_set<char> seen;
    for (int col = 0; col < 9; col++) {
        if (board[row][col] != '.') {
            if (seen.count(board[row][col]))
                return false;
            seen.insert(board[row][col]);
        }
    }
    return true;
}

bool isValidInCol(vector<vector<char>>& board, int col, int num) {
    unordered_set<char> seen;
    for (int row = 0; row < 9; row++) {
        if (board[row][col] != '.') {
            if (seen.count(board[row][col]))
                return false;
            seen.insert(board[row][col]);
        }
    }
    return true;
}

bool isValidInSubgrid(vector<vector<char>>& board, int row, int col, int num) {
    unordered_set<char> seen;
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] != '.') {
                if (seen.count(board[startRow + i][startCol + j]))
                    return false;
                seen.insert(board[startRow + i][startCol + j]);
            }
        }
    }
    return true;
}

public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int row = 0;row<board.size();row++)
        {
            for(int col=0;col<board[0].size();col++)
            {
                char num = board[row][col];
                if(num!='.'){
                    if(!isValidInRow(board,row,num))return false;
                    if(!isValidInCol(board,col,num))return false;
                    if(!isValidInSubgrid(board,row,col,num))return false;
                }
            }
        }
        return true;
    }
};
