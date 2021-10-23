//
// search.h
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


#ifndef search_h
#define search_h

#include "board.h"

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
                        cout << "Best MOVE\n";
                        bestVal = cur_val;
                        bestMove = make_tuple(x, y, get<0>(z), get<1>(z));
                    }
                    
                }
            }
        }
    }
    return bestMove;
}






#endif /* Search_h */
