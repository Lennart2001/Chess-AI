//
// board.h
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


#ifndef board_h
#define board_h

#include "piece.h"


Piece board[8][8];

void initilizeBoard() {

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (x==0) {
                switch(y) {
                    case 0: board[x][y] = Piece('R', false, x, y);
                        break;
                    case 1: board[x][y] = Piece('N', false, x, y);
                        break;
                    case 2: board[x][y] = Piece('B', false, x, y);
                        break;
                    case 3: board[x][y] = Piece('Q', false, x, y);
                        break;
                    case 4: board[x][y] = Piece('K', false, x, y);
                        break;
                    case 5: board[x][y] = Piece('B', false, x, y);
                        break;
                    case 6: board[x][y] = Piece('N', false, x, y);
                        break;
                    case 7: board[x][y] = Piece('R', false, x, y);
                        break;
                }
            } else if (x == 1) {
                board[x][y] = Piece('P', false, x, y);
            } else if (x == 6) {
                board[x][y] = Piece('P', true, x, y);
            } else if (x == 7) {
                switch(y) {
                    case 0: board[x][y] = Piece('R', true, x, y);
                        break;
                    case 1: board[x][y] = Piece('N', true, x, y);
                        break;
                    case 2: board[x][y] = Piece('B', true, x, y);
                        break;
                    case 3: board[x][y] = Piece('Q', true, x, y);
                        break;
                    case 4: board[x][y] = Piece('K', true, x, y);
                        break;
                    case 5: board[x][y] = Piece('B', true, x, y);
                        break;
                    case 6: board[x][y] = Piece('N', true, x, y);
                        break;
                    case 7: board[x][y] = Piece('R', true, x, y);
                        break;
                }
            } else {
                board[x][y] = Piece();
            }
        }
    }
}

string getString(Piece board) {
    if (board.isEmpty) {
        return "  ";
    } else {
        string s(1, board.symbol);
        if (board.isWhite) {
            return "w" + s;
        } else {
            return "b" + s;
        }
    }
}

//MARK: Print Board
void printBoard() {
    
    for (int x = 0; x < 8; x++) {
        cout << "   ";
        for (int z = 0; z < 57; z++) {
            cout << "-";
        }
        cout << "\n";
        for (int y = 0; y < 3; y++) {
            
            if (y!=1) {
                if (x%2==0) {
                    cout << "   |######|      |######|      |######|      |######|      |\n";
                } else {
                    cout << "   |      |######|      |######|      |######|      |######|\n";
                }
            } else {
                
                cout << " " << 8 - x << " |  ";
                for (int k = 0; k < 8; k++) {
                    cout << getString(board[x][k]) << "  |  ";
                }
                cout << endl;
            }
        }
    }
    cout << "   ";
    for (int z = 0; z < 57; z++) {
        cout << "-";
    }
    cout << "\n       A      B      C      D      E      F      G      H\n";
    
}

int getLetter(char c) {
    switch(c) {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default: return -1;
    }
}


int evaluateBoard(Piece board[8][8]) {
    
    int evaluation = 0;
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            switch (board[x][y].symbol) {
                case 'P': {
                    PieceValue::Pawn pawn;
                    if (!board[x][y].isWhite) {
                        evaluation += pawn.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= pawn.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                case 'N': {
                    PieceValue::Knight knight;
                    if (!board[x][y].isWhite) {
                        evaluation += knight.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= knight.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                case 'B': {
                    PieceValue::Bishop bishop;
                    if (!board[x][y].isWhite) {
                        evaluation += bishop.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= bishop.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                case 'R': {
                    PieceValue::Rook rook;
                    if (!board[x][y].isWhite) {
                        evaluation += rook.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= rook.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                case 'Q': {
                    PieceValue::Queen queen;
                    if (!board[x][y].isWhite) {
                        evaluation += queen.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= queen.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                case 'K': {
                    PieceValue::King king;
                    if (!board[x][y].isWhite) {
                        evaluation += king.getBoardValue(board[x][y].isWhite, x, y);
                    } else {
                        evaluation -= king.getBoardValue(board[x][y].isWhite, x, y);
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
    return evaluation;
}



#endif /* board_h */
