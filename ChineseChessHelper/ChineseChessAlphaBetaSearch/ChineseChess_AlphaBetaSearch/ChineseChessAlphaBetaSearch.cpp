#include <stdio.h>
#include <string.h>
#include "ChineseChessAlphaBetaSearch.h"
#include "ChineseChessEvaluatorPosition.h"
#include "ChineseChessEvaluatorChess.h"

ChineseChessAlphaBetaSearch::ChineseChessAlphaBetaSearch()
{
    ev = new ChineseChessEvaluatorPosition();
//    ev = new ChineseChessEvaluatorChess();
}

int ChineseChessAlphaBetaSearch::sign(int d)
{
    return d < 0? -1 : d > 0;
}

std::string ChineseChessAlphaBetaSearch::getChessName(char c)
{
    std::string name;

    name = "";
    switch (c)
    {
    case 'c':
    case 'C':
        name = "车";
        break;
    case 'm':
    case 'M':
        name = "马";
        break;
    case 'x':
        name = "相";
        break;
    case 'X':
        name = "象";
        break;
    case 's':
    case 'S':
        name = "士";
        break;
    case 'j':
        name = "帅";
        break;
    case 'J':
        name = "将";
        break;
    case 'p':
    case 'P':
        name = "炮";
        break;
    case 'z':
        name = "兵";
        break;
    case 'Z':
        name = "卒";
        break;
    }

    return name;
}

std::string ChineseChessAlphaBetaSearch::getNextMove(char *chessboard, bool isRed, int depth)
{
    ChessBoard cb;
    int i, j, x, y, X, Y, v;
    char movingChess, m[100];


    std::string desc;
    std::string direction[3] = {"进", "平", "退"};
    std::string col[9] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

    cnt = 0;
    this->isRed = isRed;
    strcpy(cb.board, chessboard);
    v = alpha_beta_search(&cb, depth, -0x7f7f7f7f, 0x7f7f7f7f, true);
    printf("cnt = %d\n", cnt);

    desc = "";
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 9; j++) {
            if (chessboard[i*9+j] == '0') continue;
            if (lastMove.board[i*9+j] == '0') {
                x = i; y = j;
                movingChess = chessboard[i*9+j];
                desc += getChessName(movingChess);
                desc += col[8 - j];
                break;
            }
        }
        if (j < 9) break;
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 9; j++) {
            if (lastMove.board[i*9+j] == movingChess && chessboard[i*9+j] != movingChess) {
                X = i; Y = j;
                desc += direction[sign(i - x) + 1];
                if (sign(i - x) == 0 || y != j) desc += col[8 - j];
                else desc += col[sign(i - x) * (i - x) - 1];
                break;
            }
        }
        if (j < 9) break;
    }

    sprintf(m, "\n[(%d, %d) -> (%d, %d): %d]", 9-y, 10-x, 9-Y, 10-X, v);
    return desc + m;
}


int ChineseChessAlphaBetaSearch::alpha_beta_search(ChessBoard *board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    int v;
    ChessBoard *ncb, lmove;
    ChineseChessMover mover(isRed);

    cnt++;
    v = ev->evaluate(board->board, isRed);
    if (depth == 0 || v < -4000 || v > 4000) {
        return v;
    }
    if (maximizingPlayer) {
        mover.move(board, isRed);
        mover.initializeTraverse(false);
        while ((ncb = mover.getNextMove())) {
            v = alpha_beta_search(ncb, depth - 1, alpha, beta, false);
            if (v > alpha) {
                alpha = v;
                lmove = *ncb;
            }
            if (beta <= alpha) break;
        }
        lastMove = lmove;
        return alpha;
    }
    else {
        mover.move(board, !isRed);
        mover.initializeTraverse(true);
        while ((ncb = mover.getNextMove())) {
            v = alpha_beta_search(ncb, depth - 1, alpha, beta, true);
            if (v < beta) {
                beta = v;
                lmove = *ncb;
            }
            if (beta <= alpha) break;
        }
        lastMove = lmove;
        return beta;
    }
}

void ChineseChessAlphaBetaSearch::outputInfo(ChessBoard *board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    int i, j;

    printf("Search(depth: %d, alpha: %d, beta: %d, maximizingPlayer = %s\n", depth, alpha, beta, maximizingPlayer?"True":"False");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 9; j++) {
            printf("%c", board->board[i*9+j]);
        }
        printf("\n");
    }
}
