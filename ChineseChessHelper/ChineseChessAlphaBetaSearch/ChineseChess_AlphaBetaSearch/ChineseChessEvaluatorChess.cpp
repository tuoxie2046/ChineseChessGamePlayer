#include "ChineseChessEvaluatorChess.h"

ChineseChessEvaluatorChess::ChineseChessEvaluatorChess()
{

}

int ChineseChessEvaluatorChess::evaluateSingleChess(int x, int y, char type, bool isRed)
{
    int multiplier = 0, v = 0;

    if (isRed && type >= 'a' && type <= 'z') multiplier = 1;
    else if (isRed && type >= 'A' && type <= 'Z') multiplier = -1;
    else if (!isRed && type >= 'a' && type <= 'z') multiplier = -1;
    else if (!isRed && type >= 'A' && type <= 'Z') multiplier = 1;

    switch (type) {
        case 'z':
        case 'Z':
            v = 55;
            break;
        case 'x':
        case 'X':
            v = 210;
            break;
        case 's':
        case 'S':
            v = 226;
            break;
        case 'p':
        case 'P':
            v = 442;
            break;
        case 'm':
        case 'M':
            v = 439;
            break;
        case 'C':
        case 'c':
            v = 989;
            break;
        case 'j':
        case 'J':
            v = 10000;
            break;
    }

    return v * multiplier;
}

int ChineseChessEvaluatorChess::evaluate(char *chessboard, bool isRed)
{
    int x, y, val;

    val = 0;
    for (x = 0; x < 10; x++)
        for (y = 0; y < 9; y++)
            val += evaluateSingleChess(x, y, chessboard[x*9+y], isRed);

//    return val + rand() % 5;
    return val;
}
