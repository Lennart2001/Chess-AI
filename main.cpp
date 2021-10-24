//
// main.cpp
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


static long int calculations = 0;

vector<tuple<int, int>> getLegalMoves(Piece piece, Piece board[8][8]) {
    
    
    vector<tuple<int, int>> legalMovesVector;
    
    vector<int> temp = {-1, 1};
    
    switch (piece.symbol) {
            
        case 'P': {
            
            int pawn_start = (piece.isWhite) ? 6 : 1;
            int pawn_up_down = (piece.isWhite) ? -1 : 1;
            
            // Check for Double move availability
            if (piece.current_x + pawn_up_down >= 0 && piece.current_x + pawn_up_down < 8) {
                if (board[piece.current_x + pawn_up_down][piece.current_y].isEmpty) {
                    if (piece.current_x == pawn_start) {
                        legalMovesVector.push_back(make_tuple(piece.current_x + pawn_up_down, piece.current_y));
                        if (board[piece.current_x + pawn_up_down * 2][piece.current_y].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + pawn_up_down * 2, piece.current_y));
                        }
                    }
                    legalMovesVector.push_back(make_tuple(piece.current_x + pawn_up_down, piece.current_y));
                }
                for (auto x : temp) {
                    if (piece.current_y + x < 8 && piece.current_y + x > 0) {
                        if (!board[piece.current_x + pawn_up_down][piece.current_y+x].isEmpty && board[piece.current_x + pawn_up_down][piece.current_y+x].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + pawn_up_down, piece.current_y+x));
                        }
                    }
                }
            }
            break;
        }
            
        case 'N': {
            
            for (auto x : temp) {
                if (piece.current_x + 2 * x >= 0 && piece.current_x + 2 * x < 8) {
                    for (auto y : temp) {
                        if (piece.current_y + y >= 0 && piece.current_y + y < 8) {
                            if (board[piece.current_x + 2 * x][piece.current_y + y].isWhite != piece.isWhite || board[piece.current_x + 2 * x][piece.current_y + y].isEmpty) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + 2 * x, piece.current_y + y));
                            }
                        }
                    }
                    
                }
                if (piece.current_x + x >= 0 && piece.current_x + 1 * x < 8) {
                    for (auto y : temp) {
                        if (piece.current_y + 2 * y >= 0 && piece.current_y + 2 * y < 8) {
                            if (board[piece.current_x + x][piece.current_y + 2 * y].isWhite != piece.isWhite || board[piece.current_x + x][piece.current_y + 2 * y].isEmpty) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + x, piece.current_y + 2 * y));
                            }
                        }
                    }
                }
            }
            break;
        }
            
        case 'B': {
            
            for (auto x : temp) {
                for (auto y : temp) {
                    for (int z = 1; z < 8; z++) {
                        if (piece.current_x + z * x >= 0 && piece.current_x + z * x < 8 && piece.current_y + z * y >= 0 && piece.current_y + z * y < 8) {
                            if (board[piece.current_x + z * x][piece.current_y + z * y].isEmpty) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y + z * y));
                            } else if (board[piece.current_x + z * x][piece.current_y + z * y].isWhite != piece.isWhite) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y + z * y));
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
            
        case 'R': {
            for (auto x : temp) {
                for (int z = 1; z < 8; z++) {
                    if (piece.current_x + z * x >= 0 && piece.current_x + z * x < 8) {
                        if (board[piece.current_x + z * x][piece.current_y].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y));
                        } else if (board[piece.current_x + z * x][piece.current_y].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y));
                            break;
                        } else {
                            break;
                        }
                    }
                }
                for (int z = 1; z < 8; z++) {
                    if (piece.current_y + z * x >= 0 && piece.current_y + z * x < 8) {
                        if (board[piece.current_x][piece.current_y + z * x].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + z * x));
                        } else if (board[piece.current_x][piece.current_y + z * x].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + z * x));
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
            break;
        }
            
        case 'Q': {
            
            for (auto x : temp) {
                for (int z = 1; z < 8; z++) {
                    if (piece.current_x + z * x >= 0 && piece.current_x + z * x < 8) {
                        if (board[piece.current_x + z * x][piece.current_y].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y));
                        } else if (board[piece.current_x + z * x][piece.current_y].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y));
                            break;
                        } else {
                            break;
                        }
                    }
                }
                for (int z = 1; z < 8; z++) {
                    if (piece.current_y + z * x >= 0 && piece.current_y + z * x < 8) {
                        if (board[piece.current_x][piece.current_y + z * x].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + z * x));
                        } else if (board[piece.current_x][piece.current_y + z * x].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + z * x));
                            break;
                        } else {
                            break;
                        }
                    }
                }
                for (auto y : temp) {
                    for (int z = 1; z < 8; z++) {
                        if (piece.current_x + z * x >= 0 && piece.current_x + z * x < 8 && piece.current_y + z * y >= 0 && piece.current_y + z * y < 8) {
                            if (board[piece.current_x + z * x][piece.current_y + z * y].isEmpty) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y + z * y));
                            } else if (board[piece.current_x + z * x][piece.current_y + z * y].isWhite != piece.isWhite) {
                                legalMovesVector.push_back(make_tuple(piece.current_x + z * x, piece.current_y + z * y));
                                break;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
            
        case 'K': {
            
            for (auto x : temp) {
                if (piece.current_x + x >= 0 && piece.current_x + x < 8) {
                    if (board[piece.current_x + x][piece.current_y].isEmpty) {
                        legalMovesVector.push_back(make_tuple(piece.current_x + x, piece.current_y));
                    } else if (board[piece.current_x + x][piece.current_y].isWhite != piece.isWhite) {
                        legalMovesVector.push_back(make_tuple(piece.current_x + x, piece.current_y));
                    }
                }
                if (piece.current_y + x >= 0 && piece.current_y + x < 8) {
                    if (board[piece.current_x][piece.current_y + x].isEmpty) {
                        legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + x));
                    } else if (board[piece.current_x][piece.current_y + x].isWhite != piece.isWhite) {
                        legalMovesVector.push_back(make_tuple(piece.current_x, piece.current_y + x));
                    }
                }
                for (auto y : temp) {
                    if (piece.current_x + x >= 0 && piece.current_x + x < 8 && piece.current_y + y >= 0 && piece.current_y + y < 8) {
                        if (board[piece.current_x + x][piece.current_y + y].isEmpty) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + x, piece.current_y + y));
                        } else if (board[piece.current_x + x][piece.current_y + y].isWhite != piece.isWhite) {
                            legalMovesVector.push_back(make_tuple(piece.current_x + x, piece.current_y + y));
                        }
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    
    return legalMovesVector;
    
}


int AB_Prune(Piece board[8][8], int alpha, int beta, bool isMax, int depth) {
    
    if (depth <= 0) {
        return evaluateBoard(board);
    }
    
    if (isMax) {
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (!board[x][y].isWhite && !board[x][y].isEmpty){
                    for (auto z : getLegalMoves(board[x][y], board)) {
                        calculations++;
                        
                        // Move Piece on Board to some Square
                        
                        // Piece Saver
                        Piece saved = board[get<0>(z)][get<1>(z)];
                        
                        board[get<0>(z)][get<1>(z)] = board[x][y];
                        board[get<0>(z)][get<1>(z)].update(get<0>(z), get<1>(z));
                        board[x][y] = Piece();
                        
                        //cout << endl << alpha << endl;
                        alpha = max(alpha, AB_Prune(board, alpha, beta, !isMax, depth-1));
                        //cout << endl << alpha << endl;
                        
                        // Move Piece back on Board to Original Square
                        board[x][y] = board[get<0>(z)][get<1>(z)];
                        board[x][y].update(x, y);
                        board[get<0>(z)][get<1>(z)] = saved;
                        
                        // Check Alpha vs Beta Value
                        if (alpha >= beta) {
                            return alpha;
                        }
                        
                    }
                }
            }
        }
        return alpha;
        
    } else {
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (board[x][y].isWhite && !board[x][y].isEmpty){
                    for (auto z : getLegalMoves(board[x][y], board)) {
                        calculations++;
                        
                        // Move Piece on Board to some Square
                        
                        // Piece Saver
                        Piece saved = board[get<0>(z)][get<1>(z)];
                        
                        board[get<0>(z)][get<1>(z)] = board[x][y];
                        board[get<0>(z)][get<1>(z)].update(get<0>(z), get<1>(z));
                        board[x][y] = Piece();
                        
                        beta = min(beta, AB_Prune(board, alpha, beta, !isMax, depth-1));
                        
                        
                        // Move Piece back on Board to Original Square
                        board[x][y] = board[get<0>(z)][get<1>(z)];
                        board[x][y].update(x, y);
                        board[get<0>(z)][get<1>(z)] = saved;
                        
                        // Check Alpha vs Beta Value
                        if (alpha >= beta) {
                            return beta;
                        }
                        
                    }
                }
            }
        }
        return beta;
    }
    
}

// 1) FX, FY, TX, TY
tuple<int, int, int, int> AB_Prune_Root(Piece board[8][8], int depth) {
    
    int cur_val = -1000000;
    int bestVal = -1000000;
    tuple<int, int, int, int> bestMove = {0,0,0,0};
    calculations = 0;
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (!board[x][y].isWhite && !board[x][y].isEmpty){
                for (auto z : getLegalMoves(board[x][y], board)) {
                    calculations++;
                    
                    // Create Move on Board
                    
                    // Piece Saver
                    Piece saved = board[get<0>(z)][get<1>(z)];
                    
                    board[get<0>(z)][get<1>(z)] = board[x][y];
                    board[get<0>(z)][get<1>(z)].update(get<0>(z), get<1>(z));
                    board[x][y] = Piece();
                    
                    cur_val = AB_Prune(board, -100000, 100000, false, depth);
                    
                    // Reset Board to Original Position
                    board[x][y] = board[get<0>(z)][get<1>(z)];
                    board[x][y].update(x, y);
                    board[get<0>(z)][get<1>(z)] = saved;
                    
                    if (cur_val > bestVal) {
                        bestVal = cur_val;
                        bestMove = make_tuple(x, y, get<0>(z), get<1>(z));
                    }
                    
                }
            }
        }
    }
    return bestMove;
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


//MARK: PLAYER MOVE
void playerMove() {
    
    char let_column, let_to_column;
    int int_row, int_to_row, int_column, int_to_column;
    
    cout << "From: ";
    cin >> let_column;
    cin >> int_row;
    
    cout << "To:   ";
    cin >> let_to_column;
    cin >> int_to_row;
    
    int_column = getLetter(let_column);
    int_to_column = getLetter(let_to_column);
    int_row = 8-int_row;
    int_to_row = 8-int_to_row;
    
    if (!board[int_row][int_column].isEmpty && board[int_row][int_column].isWhite) {
        for (auto x : getLegalMoves(board[int_row][int_column], board)) {
            if (make_tuple(int_to_row, int_to_column) == x) {
                board[int_to_row][int_to_column] = board[int_row][int_column];
                board[int_to_row][int_to_column].update(int_to_row, int_to_column);
                board[int_row][int_column] = Piece();
                printBoard();
                cout << evaluateBoard(board) << endl << endl;
                return;
            }
        }
        cout << "Your Destination was INVALID!\n";
    } else {
        cout << "The Square you Chose has NO Piece!\n";
    }
    playerMove();
}


//MARK: ENGINE MOVE
void engineMove() {
    
    tuple<int, int, int, int> bestMove;
    
    bestMove = AB_Prune_Root(board, 4);
    
    board[get<2>(bestMove)][get<3>(bestMove)] = board[get<0>(bestMove)][get<1>(bestMove)];
    board[get<2>(bestMove)][get<3>(bestMove)].update(get<2>(bestMove), get<3>(bestMove));
    board[get<0>(bestMove)][get<1>(bestMove)] = Piece();
    
    printBoard();
    cout << -evaluateBoard(board) << endl;
    cout << calculations << endl;
}


int main() {
    
    initilizeBoard();
    
    printBoard();
    
    while (true) {
        playerMove();
        
        engineMove();
    }
    
    return 0;
}
