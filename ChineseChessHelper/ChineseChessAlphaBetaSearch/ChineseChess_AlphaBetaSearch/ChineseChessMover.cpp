#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "ChineseChessMover.h"
#include "ChineseChessEvaluatorPosition.h"
#include "ChineseChessEvaluatorChess.h"

using std::make_pair;

bool cmp_movingstep(const MovingStep &A, const MovingStep &B)
{
    if (A.isKiller && !B.isKiller) return true;
    else if (!A.isKiller && B.isKiller) return false;
    return A.val > B.val;
}

bool cmp_movingstep_rev(const MovingStep &A, const MovingStep &B)
{
    if (A.isKiller && !B.isKiller) return true;
    else if (!A.isKiller && B.isKiller) return false;
    return A.val < B.val;
}

ChineseChessMover::ChineseChessMover(bool isRed)
{
    this->isRed = isRed;
    this->evaluator = new ChineseChessEvaluatorPosition();
//    this->evaluator = new ChineseChessEvaluatorChess();
}

bool ChineseChessMover::hasNextMove()
{
    return i != moves.end();
}

int ChineseChessMover::getNewValue(int x, int y, int X, int Y)
{
    int val;

    val = baseVal;
    val -= evaluator->evaluateSingleChess(X, Y, ori.board[X*9+Y], isRed);
    val -= evaluator->evaluateSingleChess(x, y, ori.board[x*9+y], isRed);
    val += evaluator->evaluateSingleChess(X, Y, ori.board[x*9+y], isRed);

    return val;
}

bool ChineseChessMover::isOpposed(char a, char b)
{
    if (a == '0' || b == '0') return false;
    if (a >= 'A' && a <= 'Z' && b >= 'a' && b <= 'z') return true;
    if (a >= 'a' && a <= 'z' && b >= 'A' && b <= 'Z') return true;

    return false;
}

void ChineseChessMover::initializeTraverse(bool reverse)
{
    if (!reverse) sort(moves.begin(), moves.end(), cmp_movingstep);
    else sort(moves.begin(), moves.end(), cmp_movingstep_rev);

    i = moves.begin();
    lastSrc = lastDst = -1;
}

ChessBoard *ChineseChessMover::getNextMove()
{
    MovingStep step;

    if (i == moves.end()) return NULL;

    step = *i++;
    if (lastDst != -1) {
        ori.board[lastSrc] = ori.board[lastDst];
        ori.board[lastDst] = patch;
    }

    lastSrc = step.src;
    lastDst = step.dst;
    patch = ori.board[lastDst];
    ori.board[lastDst] = ori.board[lastSrc];
    ori.board[lastSrc] = '0';

    return &ori;
}


void ChineseChessMover::moveC(int x, int y)
{
    int i, j;
    int X, Y;
    char a, b;
    const int dx[4] = {-1, 0, 0, 1};
    const int dy[4] = {0, -1, 1, 0};

    a = ori.board[x*9+y];

    for (i = 0; i < 4; i++) {
        for (j = 1; j < 10; j++) {
            X = x + dx[i] * j;
            Y = y + dy[i] * j;
            if (X < 0 || X >= 10 || Y < 0 || Y >= 9) break;

            b = ori.board[X*9+Y];
            if (b == '0') {
                moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
                continue;
            }
            else if (isOpposed(a, b)) {
                moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
            }
            break;
        }
    }
}


void ChineseChessMover::moveP(int x, int y)
{
    int i, j;
    int X, Y;
    char a, b;
    const int dx[4] = {-1, 0, 0, 1};
    const int dy[4] = {0, -1, 1, 0};

    a = ori.board[x*9+y];

    for (i = 0; i < 4; i++) {
        for (j = 1; j < 10; j++) {
            X = x + dx[i] * j;
            Y = y + dy[i] * j;
            if (X < 0 || X >= 10 || Y < 0 || Y >= 9) break;

            b = ori.board[X*9+Y];
            if (b == '0') {
                moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
                continue;
            }

            break;
        }

        //try to eat target
        for (j = j + 1; j < 10; j++) {
            X = x + dx[i] * j;
            Y = y + dy[i] * j;
            if (X < 0 || X >= 10 || Y < 0 || Y >= 9) break;
            b = ori.board[X*9+Y];
            if (b == '0') continue;
            if (isOpposed(a, b)) {
                moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
                break;
            }
            else break;
        }
    }
}

void ChineseChessMover::moveZ(int x, int y)
{
    int i, X, Y;
    char a, b;
    const int dx[4] = {-1, 0, 0, 1};
    const int dy[4] = {0, -1, 1, 0};

    a = ori.board[x*9+y];

    for (i = 0; i < 4; i++) {
        X = x + dx[i];
        Y = y + dy[i];
        if (X < 0 || X >= 10 || Y < 0 || Y >= 9) continue;
        if (isRed) {
            if (a == 'Z') {
                if (X < x) continue;
                if (X <= 4 && Y != y) continue;
            }
            if (a == 'z') {
                if (X > x) continue;
                if (X >= 5 && Y != y) continue;
            }
        }
        else {
            if (a == 'z') {
                if (X < x) continue;
                if (X <= 4 && Y != y) continue;
            }
            if (a == 'Z') {
                if (X > x) continue;
                if (X >= 5 && Y != y) continue;
            }
        }

        b = ori.board[X*9+Y];
        if (b == '0') {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
        }
        else if (isOpposed(a, b)) {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
        }
    }
}


void ChineseChessMover::moveM(int x, int y)
{
    char a, b;
    int i, X, Y;
    const int dx[8] = {1, -1, -2, -2, -1, 1, 2, 2};
    const int dy[8] = {-2, -2, -1, 1, 2, 2, 1, -1};

    a = ori.board[x*9+y];
    for (i = 0; i < 8; i++) {
        X = x + dx[i];
        Y = y + dy[i];
        if (X < 0 || X >= 10 || Y < 0 || Y >= 9) continue;
        if (abs(dx[i]) == 2 && ori.board[(dx[i]/2+x)*9+y] != '0') continue;
        if (abs(dy[i]) == 2 && ori.board[x*9+(dy[i]/2+y)] != '0') continue;
        b = ori.board[X*9+Y];
        if (b == '0') {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
        }
        else if (isOpposed(a, b)) {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
        }
    }
}


void ChineseChessMover::moveX(int x, int y)
{
    char a, b;
    int i, X, Y;
    const int dx[4] = {-2, -2, 2, 2};
    const int dy[4] = {-2, 2, 2, -2};

    a = ori.board[x*9+y];
    for (i = 0; i < 4; i++) {
        X = x + dx[i];
        Y = y + dy[i];
        if (X < 0 || X >= 10 || Y < 0 || Y >= 9) continue;
        if (ori.board[(x+dx[i]/2)*9+(y+dy[i]/2)] != '0') continue;
        if (isRed) {
            if (a == 'X' && X >= 5) continue;
            if (a == 'x' && X < 5) continue;
        }
        else {
            if (a == 'x' && X >= 5) continue;
            if (a == 'X' && X < 5) continue;
        }
        b = ori.board[X*9+Y];
        if (b == '0') {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
        }
        else if (isOpposed(a, b)) {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
        }
    }
}


void ChineseChessMover::moveS(int x, int y)
{
    char a, b;
    int i, X, Y;
    const int dx[4] = {-1, 1, 1, -1};
    const int dy[4] = {-1, -1, 1, 1};

    a = ori.board[x*9+y];
    for (i = 0; i < 4; i++) {
        X = x + dx[i];
        Y = y + dy[i];
        if (X < 0 || X >= 10 || Y < 3 || Y > 5) continue;
        if (isRed) {
            if (a == 'S' && X > 2) continue;
            if (a == 's' && X < 7) continue;
        }
        else {
            if (a == 's' && X > 2) continue;
            if (a == 'S' && X < 7) continue;
        }
        b = ori.board[X*9+Y];
        if (b == '0') {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
        }
        else if (isOpposed(a, b)) {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
        }
    }
}

void ChineseChessMover::moveJ(int x, int y)
{
    char a, b;

    int i, X, Y;
    const int dx[4] = {-1, 0, 0, 1};
    const int dy[4] = {0, -1, 1, 0};

    a = ori.board[x*9+y];

    // try to eat opp-jiang
    if (x > 4) {
        for (i = x - 1; i >= 0; i--)
            if (ori.board[i*9+y] != '0') break;
    }
    else {
        for (i = x + 1; i < 10; i++)
            if (ori.board[i*9+y] != '0') break;
    }
    if (ori.board[i*9+y] == 'j' || ori.board[i*9+y] == 'J') {
        moves.push_back(MovingStep(x*9+y, i*9+y, getNewValue(x, y, i, y), true));
    }


    for (i = 0; i < 4; i++) {
        X = x + dx[i];
        Y = y + dy[i];
        if (X < 0 || X >= 10 || Y < 3 || Y > 5) continue;
        if (isRed) {
            if (a == 'S' && X > 2) continue;
            if (a == 's' && X < 7) continue;
        }
        else {
            if (a == 's' && X > 2) continue;
            if (a == 'S' && X < 7) continue;
        }
        b = ori.board[X*9+Y];
        if (b == '0') {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), false));
        }
        else if (isOpposed(a, b)) {
            moves.push_back(MovingStep(x*9+y, X*9+Y, getNewValue(x, y, X, Y), true));
        }
    }
}


void ChineseChessMover::move(int x, int y)
{
    char a;

    baseVal = evaluator->evaluate(ori.board, isRed);

    a = ori.board[x*9+y];
    if (a >= 'a') a -= ('a' - 'A');

    if (a == 'Z') moveZ(x, y);
    if (a == 'P') moveP(x, y);
    if (a == 'C') moveC(x, y);
    if (a == 'M') moveM(x, y);
    if (a == 'X') moveX(x, y);
    if (a == 'S') moveS(x, y);
    if (a == 'J') moveJ(x, y);
}

void ChineseChessMover::move(ChessBoard *ori, bool movingRed)
{
    int x, y;

    moves.clear();
    this->ori = *ori;

    for (x = 0; x < 10; x++) {
        for (y = 0; y < 9; y++) {
            if (ori->board[x*9+y] >= 'a' && ori->board[x*9+y] <= 'z' && movingRed)
                move(x, y);
            else if (ori->board[x*9+y] >= 'A' && ori->board[x*9+y] <= 'Z' && !movingRed)
                move(x, y);
        }
    }
}
