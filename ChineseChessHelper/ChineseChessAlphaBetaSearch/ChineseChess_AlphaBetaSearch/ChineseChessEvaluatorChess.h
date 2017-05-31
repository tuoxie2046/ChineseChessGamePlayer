#ifndef CHINESECHESSEVALUATORCHESS_H
#define CHINESECHESSEVALUATORCHESS_H

#include "ChineseChessEvaluator.h"

class ChineseChessEvaluatorChess: public ChineseChessEvaluator
{
public:
    ChineseChessEvaluatorChess();
    int evaluateSingleChess(int x, int y, char type, bool isRed);
    int evaluate(char *chessboard, bool isRed);
};

#endif // CHINESECHESSEVALUATORCHESS_H
