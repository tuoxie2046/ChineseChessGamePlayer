#ifndef CHINESECHESSMOVER_H
#define CHINESECHESSMOVER_H

#include <vector>
#include "ChineseChessEvaluator.h"

struct ChessBoard
{
    char board[91];
};

struct MovingStep
{
    MovingStep() {}
    MovingStep(int s, int d, int v, bool isk) {
        src = s;
        dst = d;
        val = v;
        isKiller = isk;
    }

    int src, dst, val;
    bool isKiller;
};

class ChineseChessMover
{
public:
    ChineseChessMover(bool isRed);
    void move(ChessBoard *ori, bool movingRed);
    void initializeTraverse(bool reverse);
    ChessBoard *getNextMove();
    bool hasNextMove();
private:
    bool isOpposed(char a, char b);
    void move(int x, int y);
    void moveZ(int x, int y);
    void moveC(int x, int y);
    void moveP(int x, int y);
    void moveM(int x, int y);
    void moveX(int x, int y);
    void moveS(int x, int y);
    void moveJ(int x, int y);
    int getNewValue(int x, int y, int X, int Y);
private:
    bool isRed;

    ChessBoard ori;
    char patch;
    int lastSrc, lastDst, baseVal;

    std::vector<MovingStep>::iterator i;
    std::vector<MovingStep> moves;
    ChineseChessEvaluator *evaluator;
};

#endif // CHINESECHESSMOVER_H
