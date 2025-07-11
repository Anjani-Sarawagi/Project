#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int a, int b, char digit) {
        // check horizontally
        for (int j = 0; j < 9; j++) {
            if (board[a][j] == digit) return false;
        }
        // check vertically
        for (int i = 0; i < 9; i++) {
            if (board[i][b] == digit) return false;
        }
        // check 3x3 box
        int startingRow = (a / 3) * 3;
        int startingCol = (b / 3) * 3;
        for (int i = startingRow; i <= startingRow + 2; i++) {
            for (int j = startingCol; j <= startingCol + 2; j++) {
                if (board[i][j] == digit) return false;
            }
        }
        return true;
    }

    bool helper(vector<vector<char>>& board, int row, int col) {
        if (row == 9) return true;  // base case
        int nextRow = row;
        int nextCol = col + 1;
        if (nextCol == 9) {
            nextRow = row + 1;
            nextCol = 0;
        }

        if (board[row][col] != '.') {
            return helper(board, nextRow, nextCol);
        }

        for (char digit = '1'; digit <= '9'; digit++) {
            if (isSafe(board, row, col, digit)) {
                board[row][col] = digit;
                if (helper(board, nextRow, nextCol)) {
                    return true;
                } else {
                    board[row][col] = '.';  // backtrack
                }
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
};

// Function to print sudoku board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    Solution solver;
    cout << "Original Sudoku Board:\n";
    printBoard(board);

    solver.solveSudoku(board);

    cout << "\nSolved Sudoku Board:\n";
    printBoard(board);

    return 0;
}
