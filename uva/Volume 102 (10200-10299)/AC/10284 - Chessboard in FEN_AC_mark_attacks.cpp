#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const int SIZE = 8;
const int KING_MOVES[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
    {0, 1}, {1, -1}, {1, 0}, {1, 1}
};
const int KNIGHT_MOVES[8][2] = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
};
const int ROOK_DIRECTIONS[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};
const int BISHOP_DIRECTIONS[4][2] = {
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

bool insideBoard(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

void markSquare(bool attacked[SIZE][SIZE], int row, int col) {
    if (insideBoard(row, col)) {
        attacked[row][col] = true;
    }
}

void markRays(const char board[SIZE][SIZE], bool attacked[SIZE][SIZE],
              int row, int col, const int directions[][2]) {
    for (int i = 0; i < 4; ++i) {
        int nextRow = row + directions[i][0];
        int nextCol = col + directions[i][1];
        while (insideBoard(nextRow, nextCol)) {
            if (board[nextRow][nextCol] != '.') break;
            attacked[nextRow][nextCol] = true;
            nextRow += directions[i][0];
            nextCol += directions[i][1];
        }
    }
}

int countSafeSquares(const string& fen) {
    char board[SIZE][SIZE];
    bool attacked[SIZE][SIZE] = {};
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) board[row][col] = '.';
    }

    int row = 0;
    int col = 0;
    for (char ch : fen) {
        if (ch == '/') {
            ++row;
            col = 0;
        } else if (ch >= '1' && ch <= '8') {
            col += ch - '0';
        } else {
            board[row][col++] = ch;
        }
    }

    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            char piece = board[row][col];
            if (piece == '.') continue;

            char type = static_cast<char>(tolower(static_cast<unsigned char>(piece)));
            if (type == 'p') {
                int forward = (piece == 'P') ? -1 : 1;
                markSquare(attacked, row + forward, col - 1);
                markSquare(attacked, row + forward, col + 1);
            } else if (type == 'n' || type == 'k') {
                const int (*moves)[2] = (type == 'n') ? KNIGHT_MOVES : KING_MOVES;
                for (int i = 0; i < 8; ++i) {
                    markSquare(attacked, row + moves[i][0], col + moves[i][1]);
                }
            } else {
                if (type == 'r' || type == 'q') {
                    markRays(board, attacked, row, col, ROOK_DIRECTIONS);
                }
                if (type == 'b' || type == 'q') {
                    markRays(board, attacked, row, col, BISHOP_DIRECTIONS);
                }
            }
        }
    }

    int safe = 0;
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (board[row][col] == '.' && !attacked[row][col]) ++safe;
        }
    }
    return safe;
}

int main() {
    string fen;
    while (cin >> fen) {
        cout << countSafeSquares(fen) << '\n';
    }
    return 0;
}
