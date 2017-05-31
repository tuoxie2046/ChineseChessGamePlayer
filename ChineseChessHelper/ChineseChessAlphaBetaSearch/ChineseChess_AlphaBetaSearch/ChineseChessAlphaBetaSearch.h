#ifndef CHINESECHESSALPHABETASEARCH_H
#define CHINESECHESSALPHABETASEARCH_H

#include <string>
#include <vector>

#include "ChineseChessEvaluator.h"
#include "ChineseChessMover.h"

class ChineseChessAlphaBetaSearch
{
public:
    ChineseChessAlphaBetaSearch();
    std::string getNextMove(char *chessboard, bool isRed, int depth = 5);
private:
    int sign(int d);
    void outputInfo(ChessBoard *board, int depth, int alpha, int beta, bool maximizingPlayer);
    std::string getChessName(char c);
    int alpha_beta_search(ChessBoard *board, int depth, int alpha, int beta, bool maximizingPlayer);
private:
    int cnt;
    bool isRed;
    ChessBoard lastMove;
    ChineseChessEvaluator *ev;
};

#endif // CHINESECHESSALPHABETASEARCH_H
