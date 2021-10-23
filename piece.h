//
// piece.h
//
// --- Version: 2.0.0 Caileb
//      --- Chess AI by Lennart Buhl
// --- Created: 10/19/21
//      --- By Lennart Buhl
// --- Author:
//      --- Lennart Buhl (Git - @Lennart2001)
// --- Repository:
//      --- https://github.com/Lennart2001/Caileb-2.0
// --- LinkedIn:
//      --- https://www.linkedin.com/in/lennart-buhl
//
// Min-max Searching
// https://www.cs.cornell.edu/courses/cs312/2002sp/lectures/rec21.htm
// Alpha-beta pruning
// https://www.cs.cornell.edu/courses/cs312/2002sp/lectures/rec21.htm
//


#ifndef piece_h
#define piece_h

#include <iostream>
#include <vector>

using namespace std;

struct PieceValue {
    
    struct Pawn {
        
        int pawnVal = 100;
        
        int white_board[8][8] = {
            {  0,  0,  0,  0,  0,  0,  0,  0 },
            { 50, 50, 50, 50, 50, 50, 50, 50 },
            { 10, 10, 20, 30, 30, 20, 10, 10 },
            {  5,  5, 10, 25, 25, 10,  5,  5 },
            {  0,  0,  0, 20, 20,  0,  0,  0 },
            {  5, -5,-10,  0,  0,-10, -5,  5 },
            {  5, 10, 10,-20,-20, 10, 10,  5 },
            {  0,  0,  0,  0,  0,  0,  0,  0 }
        };
        
        int black_board[8][8] = {
            {  0,  0,  0,  0,  0,  0,  0,  0 },
            {  5, 10, 10,-20,-20, 10, 10,  5 },
            {  5, -5,-10,  0,  0,-10, -5,  5 },
            {  0,  0,  0, 20, 20,  0,  0,  0 },
            {  5,  5, 10, 25, 25, 10,  5,  5 },
            { 10, 10, 20, 30, 30, 20, 10, 10 },
            { 50, 50, 50, 50, 50, 50, 50, 50 },
            {  0,  0,  0,  0,  0,  0,  0,  0 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + pawnVal;
            } else {
                return black_board[src_x][src_y] + pawnVal;
            }
        }
        
    };

    struct Knight {
        
        int knightVal = 320;
        
        int white_board[8][8] = {
            { -50, -40, -30, -30, -30, -30, -40, -50 },
            { -40, -20,   0,   0,   0,   0, -20, -40 },
            { -30,   0,  10,  15,  15,  10,   0, -30 },
            { -30,   5,  15,  20,  20,  15,   5, -30 },
            { -30,   0,  15,  20,  20,  15,   0, -30 },
            { -30,   5,  10,  15,  15,  10,   5, -30 },
            { -40, -20,   0,   5,   5,   0, -20, -40 },
            { -50, -40, -30, -30, -30, -30, -40, -50 }
        };
        
        
        int black_board[8][8] = {
            { -50, -40, -30, -30, -30, -30, -40, -50 },
            { -40, -20,   0,   5,   5,   0, -20, -40 },
            { -30,   5,  10,  15,  15,  10,   5, -30 },
            { -30,   0,  15,  20,  20,  15,   0, -30 },
            { -30,   5,  15,  20,  20,  15,   5, -30 },
            { -30,   0,  10,  15,  15,  10,   0, -30 },
            { -40, -20,   0,   0,   0,   0, -20, -40 },
            { -50, -40, -30, -30, -30, -30, -40, -50 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + knightVal;
            } else {
                return black_board[src_x][src_y] + knightVal;
            }
        }
        
    };

    struct Bishop {
        
        int bishopVal = 330;

        int white_board[8][8] = {
            { -20,-10,-10,-10,-10,-10,-10,-20 },
            { -10,  0,  0,  0,  0,  0,  0,-10 },
            { -10,  0,  5, 10, 10,  5,  0,-10 },
            { -10,  5,  5, 10, 10,  5,  5,-10 },
            { -10,  0, 10, 10, 10, 10,  0,-10 },
            { -10, 10, 10, 10, 10, 10, 10,-10 },
            { -10,  5,  0,  0,  0,  0,  5,-10 },
            { -20,-10,-10,-10,-10,-10,-10,-20 }
        };
        
        int black_board[8][8] = {
            { -20,-10,-10,-10,-10,-10,-10,-20 },
            { -10,  5,  0,  0,  0,  0,  5,-10 },
            { -10, 10, 10, 10, 10, 10, 10,-10 },
            { -10,  0, 10, 10, 10, 10,  0,-10 },
            { -10,  5,  5, 10, 10,  5,  5,-10 },
            { -10,  0,  5, 10, 10,  5,  0,-10 },
            { -10,  0,  0,  0,  0,  0,  0,-10 },
            { -20,-10,-10,-10,-10,-10,-10,-20 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + bishopVal;
            } else {
                return black_board[src_x][src_y] + bishopVal;
            }
        }
        
    };

    struct Rook {
        
        int rookVal = 500;
        
        int white_board[8][8] = {
            {  0,  0,  0,  0,  0,  0,  0,  0 },
            {  5, 10, 10, 10, 10, 10, 10,  5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            {  0,  0,  0,  5,  5,  0,  0,  0 }
        };
        
        int black_board[8][8] = {
            {  0,  0,  0,  5,  5,  0,  0,  0 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            { -5,  0,  0,  0,  0,  0,  0, -5 },
            {  5, 10, 10, 10, 10, 10, 10,  5 },
            {  0,  0,  0,  0,  0,  0,  0,  0 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + rookVal;
            } else {
                return black_board[src_x][src_y] + rookVal;
            }
        }
        
    };

    struct Queen {
        
        int queenVal = 900;
        
        int white_board[8][8] = {
            { -20,-10,-10, -5, -5,-10,-10,-20 },
            { -10,  0,  0,  0,  0,  0,  0,-10 },
            { -10,  0,  5,  5,  5,  5,  0,-10 },
            {  -5,  0,  5,  5,  5,  5,  0, -5 },
            {   0,  0,  5,  5,  5,  5,  0, -5 },
            { -10,  5,  5,  5,  5,  5,  0,-10 },
            { -10,  0,  5,  0,  0,  0,  0,-10 },
            { -20,-10,-10, -5, -5,-10,-10,-20 }
        };
        
        int black_board[8][8] = {
            { -20,-10,-10, -5, -5,-10,-10,-20 },
            { -10,  0,  5,  0,  0,  0,  0,-10 },
            { -10,  5,  5,  5,  5,  5,  0,-10 },
            {   0,  0,  5,  5,  5,  5,  0, -5 },
            {  -5,  0,  5,  5,  5,  5,  0, -5 },
            { -10,  0,  5,  5,  5,  5,  0,-10 },
            { -10,  0,  0,  0,  0,  0,  0,-10 },
            { -20,-10,-10, -5, -5,-10,-10,-20 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + queenVal;
            } else {
                return black_board[src_x][src_y] + queenVal;
            }
        }
        
    };

    struct King {
        
        int kingVal = 10000;
        
        int white_board[8][8] = {
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -20,-30,-30,-40,-40,-30,-30,-20 },
            { -10,-20,-20,-20,-20,-20,-20,-10 },
            {  20, 20,  0,  0,  0,  0, 20, 20 },
            {  20, 30, 10,  0,  0, 10, 30, 20 }
        };
        
        int black_board[8][8] = {
            {  20, 30, 10,  0,  0, 10, 30, 20 },
            {  20, 20,  0,  0,  0,  0, 20, 20 },
            { -10,-20,-20,-20,-20,-20,-20,-10 },
            { -20,-30,-30,-40,-40,-30,-30,-20 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 },
            { -30,-40,-40,-50,-50,-40,-40,-30 }
        };
        
        int getBoardValue(bool isWhite, int src_x, int src_y) {
            if (isWhite) {
                return white_board[src_x][src_y] + kingVal;
            } else {
                return black_board[src_x][src_y] + kingVal;
            }
        }
    };

};

struct Piece:PieceValue {
    
    int current_x, current_y;
    char symbol;
    bool isEmpty, isWhite;
    
    Piece(char sym, bool white, int x, int y) {
        symbol = sym;
        isEmpty = false;
        isWhite = white;
        current_x = x;
        current_y = y;
    }
    
    Piece() {
        isEmpty = true;
    }
    
    void update(int x, int y) {
        current_x = x;
        current_y = y;
    }

};

#endif /* piece_h */
