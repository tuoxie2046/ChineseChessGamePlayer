#ifndef CHINESECHESSEVALUATORPOSITION_H
#define CHINESECHESSEVALUATORPOSITION_H

#include "ChineseChessEvaluator.h"

class ChineseChessEvaluatorPosition: public ChineseChessEvaluator
{
public:
    ChineseChessEvaluatorPosition();
    int evaluateSingleChess(int x, int y, char type, bool isRed);
    int evaluate(char *chessboard, bool isRed);
};

#endif // CHINESECHESSEVALUATORPOSITION_H
