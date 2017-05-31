#include <string>
#include <stdio.h>
#include <iostream>
#include "ChineseChessAlphaBetaSearch.h"

using namespace std;

const char *filepath = "tmp/chessboard.txt";

int main()
{
    int i;
    bool isRed = false;
    char s[10], chessboard[91];
    ChineseChessAlphaBetaSearch searcher;

    freopen(filepath, "r", stdin);

    scanf("%s", s);
    if (s[0] == 'r') isRed = true;
    for (i = 0; i < 90; i++) {
        scanf("%s", s);
        chessboard[i] = s[0];
    }
    chessboard[90] = 0;

    cout << searcher.getNextMove(chessboard, isRed, 5) << endl;

    return 0;
}
