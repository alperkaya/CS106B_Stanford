
#include "marbleboard.h"
#include "grid.h"
#include "set.h"
#include "vector.h"
#include "marbletypes.h"
#include "marbleutil.h"
#include "compression.h"

using namespace std;
Set<BoardEncoding> boardHistory;

bool solvePuzzle(Grid<Marble>& board, int marbleCount, Vector<Move>& moveHistory) {
    if(marbleCount<=1){
        return true;
    }

    Vector<Move> possibleMoves=findPossibleMoves(board);

    for(int i=0; i<possibleMoves.size(); i++){
            makeMove(possibleMoves[i], board);
            BoardEncoding currentBoardEncode=compressBoard(board);
            if(!boardHistory.contains(currentBoardEncode)){
                moveHistory.add(possibleMoves[i]);

                if(solvePuzzle(board, marbleCount-1, moveHistory)){
                    boardHistory.clear();
                    return true;
                }

                moveHistory.remove(moveHistory.size()-1);
            }else{
                cout << boardHistory.size() << endl;
            }

            undoMove(possibleMoves[i], board);
            boardHistory.add(currentBoardEncode);
    }

    return false;
}
