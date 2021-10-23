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


#include "search.h"


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
}


int main() {
    
    initilizeBoard();
    
    printBoard();
    
    while (true) {
        playerMove();
        
        engineMove();
        cout << calculations << endl;
        cout << -evaluateBoard(board) << endl;
    }
    
    return 0;
}
