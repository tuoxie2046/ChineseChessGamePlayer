#ifndef CHINESECHESSEVALUATOR_H
#define CHINESECHESSEVALUATOR_H

class ChineseChessEvaluator
{
public:
    virtual int evaluateSingleChess(int x, int y, char type, bool isRed) = 0;
    virtual int evaluate(char *chessboard, bool isRed) = 0;
};

#endif // CHINESECHESSEVALUATOR_H
